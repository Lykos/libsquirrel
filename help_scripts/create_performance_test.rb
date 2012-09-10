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
    @actual.to_s + ";"
  end

end

class CaseGenerator

  def test_method_body
    bla = tests.collect { |c| INDENTATION + c.to_s}
    join_indent(fetching) + "\n\n" +
      join_indent(start_timer) + "\n" +
      join_indent(construction.collect {|c| INDENTATION + c}) + "\n\n" +
      join_indent(bla) + "\n" +
      join_indent(end_timer)
  end

  def start_timer
    ["for (unsigned int i = 0; i < #{MEASUREMENTS}; ++i) {",
     "m_timer.start();",
     "for (unsigned int j = 0; i < #{ITERATIONS}; ++i) {"]
  end

  def end_timer
    ["}",
     "m_results.push_back(PerformanceResult(\"#{@name}\", m_timer.elapsed()));",
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
    cpp.puts CPP_HEADER

    [INC, DEC].each do |generator|
      cpp.puts generator.generate_special(1, (1 << limits[:inc_dec]) - 1)
      cpp.puts
    end

    [RIGHT_SHIFT, LEFT_SHIFT].each do |generator|
      cpp.puts generator.generate_nospecial(TESTS, 1 << limits[:shift_number], limits[:shift_offset])
      cpp.puts
    end

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
