#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'
require 'yaml'

include Generators

TESTS = 1
ITERATIONS = 1000
MEASUREMENTS = 5
USED_MEASUREMENTS = 2

class Test

  def to_s
    if @actual =~ /\s|\.|\+|\-/ && !(@actual =~ /=|eq/)
      @actual + ";"
    else
      ""
    end
  end

end

class CaseGenerator

  def test_method_body
    bla = tests.collect { |c| INDENTATION * 2 + c.to_s}
    join_indent(fetching) + "\n\n" +
      join_indent(start_timer) +
      join_indent(construction.collect {|c| INDENTATION * 2 + c}) + "\n" +
      join_indent(bla) +
      join_indent(end_timer)
  end

  def title
    self.class
  end

  def start_timer
    ["Heap<PerformanceResult, CompareMilliseconds> measurements;",
     "for (unsigned int i = 0; i < MEASUREMENTS; ++i) {",
     INDENTATION + "m_timer.start();",
     INDENTATION + "for (unsigned int j = 0; j < ITERATIONS; ++j) {"]
  end

  def end_timer
    [INDENTATION + "}",
     INDENTATION + "measurements.push(PerformanceResult(\"#{@name}\", m_timer.elapsed()));",
     "}",
     "for (unsigned int i = 0; i < USED_MEASUREMENTS; ++i) {",
     INDENTATION + "m_results.push_back(measurements.pop());",
     "}"]
  end

  def generate_special(n, special)
    generate(n, [1], [], [special])
  end

  def generate_nospecial(n, limit)
    generate(n, [1], [limit], [])
  end

end

class BinaryGenerator

  def generate_nospecial(n, limit1, limit2)
    generate(n, [1], [1], [limit1], [limit2], [], [])
  end

end

limits = YAML::load(File.read(File.join(File.dirname(__FILE__), 'performance_limits.yml')))

File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.h'), 'r') do |h|
  File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.cpp'), 'w') do |cpp|
    cpp.puts "#include \"performanceresult.h\""
    cpp.puts "#include \"DataStructures/heap.h\""
    cpp.puts "#include \"comparemilliseconds.h\""
    cpp.puts "#define MEASUREMENTS #{MEASUREMENTS}"
    cpp.puts "#define USED_MEASUREMENTS #{USED_MEASUREMENTS}"
    cpp.puts "#define ITERATIONS #{ITERATIONS}"
    cpp.puts CPP_HEADER

    [INC, DEC].each do |generator|
      cpp.puts generator.generate_special(1, (1 << limits[:inc_dec]) - 1)
      cpp.puts
    end

    cpp.puts LEFT_SHIFT.generate_nospecial(TESTS, 1 << limits[:left_shift_number], limits[:left_shift_offset])
    cpp.puts

    cpp.puts RIGHT_SHIFT.generate_nospecial(TESTS, 1 << limits[:right_shift_number], limits[:right_shift_offset])

    [PLUS, MINUS].each do |generator|
      cpp.puts generator.generate_nospecial(TESTS, 1 << limits[:plus_minus], 1 << limits[:plus_minus])
      cpp.puts
    end

    cpp.puts TIMES.generate_nospecial(TESTS, 1 << limits[:times], 1 << limits[:times])
    cpp.puts

    cpp.puts MODULO.generate_nospecial(TESTS, 1 << limits[:modulo_dividend], 1 << limits[:modulo_divisor])
    cpp.puts

    cpp.puts DIVIDED.generate_nospecial(TESTS, 1 << limits[:divide_dividend], 1 << limits[:divide_divisor])
    cpp.puts

    cpp.puts POWER.generate_nospecial(TESTS, 1 << limits[:power_base], limits[:power_exponent])
    cpp.puts
  end
end
