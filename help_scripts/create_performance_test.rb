#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'
require 'yaml'

include Generators

TESTS = 2
ITERATIONS = 10
MEASUREMENTS = 10
USED_MEASUREMENTS = 2
TEST_DIRECTORY = '../performance_inputs'

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

  def line(*args)
    args.collect { |a| sprintf("%s%x", a >= 0 ? "" : "-", a.abs) }.join(" ")
  end

  def data_method_body(n, *args)
    File.open(File.join(File.dirname(__FILE__), TEST_DIRECTORY, @name + ".txt"), 'w') do |f|
      cases = generate_cases(n, *args)
      f.puts cases.length
      cases.each { |c| f.puts c }
    end
    join_indent(column_declarations[0..-2]) + "\n" +
      join_indent(["ifstream f (\"#{File.join(TEST_DIRECTORY, @name + ".txt")}\");",
                   "int lines;",
                   "f >> lines;",
                   "f.flags(ios_base::hex);",
                   "for (int i = 0; i < lines; ++i) {"] +
                    data_columns[0..-2].collect { |c| INDENTATION + c.typename + " " + c.name + ";" } +
                  [INDENTATION + "f >> " + data_columns[0..-2].collect { |c| c.name }.join(" >> ") + ";",
                   INDENTATION + "QTest::newRow(\"#{@name}\") << " + data_columns[0..-2].collect { |c| c.name }.join(" << ") + ";",
                   "}",
                   "f.close();"])
  end

  def test_method_body
    bla = tests.collect { |c| INDENTATION * 2 + c.to_s}
    join_indent(fetching[0..-2]) + "\n\n" +
      join_indent(start_timer) +
      join_indent(construction.collect {|c| INDENTATION * 2 + c}) + "\n" +
      join_indent(bla) +
      join_indent(end_timer)
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
verbose = ARGV.any? { |a| a == "-v" || a == "--verbose" }

File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.h'), 'r') do |h|
  File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.cpp'), 'w') do |cpp|
    cpp.puts "#include \"performanceresult.h\""
    cpp.puts "#include \"DataStructures/heap.h\""
    cpp.puts "#include \"comparemilliseconds.h\""
    cpp.puts "#include <fstream>"
    cpp.puts "#define MEASUREMENTS #{MEASUREMENTS}"
    cpp.puts "#define USED_MEASUREMENTS #{USED_MEASUREMENTS}"
    cpp.puts "#define ITERATIONS #{ITERATIONS}"
    cpp.puts CPP_HEADER
    cpp.puts "using namespace DataStructures;"

    puts "Created header" if verbose

    [INC, DEC].each do |generator|
      cpp.puts generator.generate_special(1, (1 << limits[:inc_dec]) - 1)
      cpp.puts
      puts "Created #{generator.name}" if verbose
    end

    cpp.puts LEFT_SHIFT.generate_nospecial(TESTS, 1 << limits[:left_shift_number], limits[:left_shift_offset])
    cpp.puts
    puts "Created #{LEFT_SHIFT.name}" if verbose

    cpp.puts RIGHT_SHIFT.generate_nospecial(TESTS, 1 << limits[:right_shift_number], limits[:right_shift_offset])
    cpp.puts
    puts "Created #{RIGHT_SHIFT.name}" if verbose

    [PLUS, MINUS].each do |generator|
      cpp.puts generator.generate_nospecial(TESTS, 1 << limits[:plus_minus], 1 << limits[:plus_minus])
      cpp.puts
      puts "Created #{generator.name}" if verbose
    end

    cpp.puts TIMES.generate_nospecial(TESTS, 1 << limits[:times], 1 << limits[:times])
    cpp.puts
    puts "Created #{TIMES.name}" if verbose

    cpp.puts MODULO.generate_nospecial(TESTS, 1 << limits[:modulo_dividend], 1 << limits[:modulo_divisor])
    cpp.puts
    puts "Created #{MODULO.name}" if verbose

    cpp.puts DIVIDED.generate_nospecial(TESTS, 1 << limits[:divide_dividend], 1 << limits[:divide_divisor])
    cpp.puts
    puts "Created #{DIVIDED.name}" if verbose

    # cpp.puts POWER.generate_nospecial(TESTS, 1 << limits[:power_base], limits[:power_exponent])
    # cpp.puts
    # puts "Created #{POWER.name}" if verbose
  end
end
