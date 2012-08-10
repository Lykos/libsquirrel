#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'
require 'yaml'

include Generators

NUMBER = 1
DUMMY = 1

class Test

  def to_s
    @actual.to_s + ";"
  end

end

class CaseGenerator

  def start_timer
    INDENTATION + "m_timer.start();\n"
  end

  def end_timer
    INDENTATION + "std::cout << \"#{@name} \" << m_timer.elapsed() << \" ms\" << std::endl;\n" +
    INDENTATION + "m_results.push(PerformanceResult(\"#{@name}\", m_timer.elapsed()));\n"
  end

  def generate_special(special)
    @number = NUMBER
    generate([1], [], [special])
  end

  def generate_nospecial(limit)
    @number = NUMBER
    generate([1], [limit], [])
  end

  def line(*args)
      s = "QTest::newRow(\"#{title(*args)}\")"
      raise "not the right number of arguments" unless args.length + 1 == data_columns.length
      args.push(DUMMY)
      args.each_with_index do |arg, i|
        bla = data_columns[i].construct(arg)
        s += whitespace(bla) + "<< " + bla
      end
      s + ";"
  end

end

class BinaryGenerator

  def generate_nospecial(limit1, limit2)
    @number = NUMBER
    generate([1], [1], [limit1], [limit2], [], [])
  end

end

limits = YAML::load(File.read(File.join(File.dirname(__FILE__), 'performance_limits.yml')))

File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.cpp'), 'w') do |f|
  f.puts "#include <iostream>"
  f.puts "#include \"performanceresult.h\""
  f.puts HEADER

  f.puts STRING_CONSTRUCTOR.generate_nospecial(1 << limits[:string_constructor])
  f.puts

  [INC, DEC].each do |generator|
    f.puts generator.generate_special((1 << limits[:inc_dec]) - 1)
    f.puts
  end

  [PLUS, MINUS].each do |generator|
    f.puts generator.generate_nospecial(1 << limits[:plus_minus], 1 << limits[:plus_minus])
    f.puts
  end

  f.puts TIMES.generate_nospecial(1 << limits[:times], 1 << limits[:times])
  f.puts

  f.puts MODULO.generate_nospecial(1 << limits[:modulo_dividend], 1 << limits[:modulo_divisor])
  f.puts

  f.puts DIVIDED.generate_nospecial(1 << limits[:divide_dividend], 1 << limits[:divide_divisor])
  f.puts

  f.puts POWER.generate_nospecial(1 << limits[:power_base], limits[:power_exponent])
  f.puts
end
