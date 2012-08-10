#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'

include Generators

NUMBER = 1

class CaseGenerator

  def start_timer
    INDENTATION + "std::cout << \"bla\" << std::endl;\n" +
    INDENTATION + "m_timer.start();\n"
  end

  def end_timer
    INDENTATION + "std::cout << \"#{@name} \" << m_timer.elapsed() << std::endl;\n" +
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

end

class BinaryGenerator

  def generate_nospecial(limit1, limit2)
    @number = NUMBER
    generate([1], [1], [limit1], [limit2], [], [])
  end

end

File.open(File.join(File.dirname(__FILE__), '..', 'PerformanceDataStructures', 'longinttest.cpp'), 'w') do |f|
  f.puts "#include <iostream>"
  f.puts "#include \"performanceresult.h\""
  f.puts HEADER

  f.puts STRING_CONSTRUCTOR.generate_nospecial(10)#(1 << 2685)
  f.puts

  [INC, DEC].each do |generator|
    f.puts generator.generate_special((1 << 1000000) - 1)
    f.puts
  end

  [RIGHT_SHIFT, LEFT_SHIFT].each do |generator|
    f.puts generator.generate_nospecial(1 << 1000000, 300)
    f.puts
  end

  [PLUS, MINUS].each do |generator|
    f.puts generator.generate_nospecial(1 << 100000, 1 << 100000)
    f.puts
  end

  f.puts TIMES.generate_nospecial(1 << 8000, 1 << 8000)
  f.puts

  f.puts MODULO.generate_nospecial(1 << 16000, 1 << 8000)
  f.puts

  f.puts DIVIDED.generate_nospecial(1 << 14000, 1 << 7000)
  f.puts

  f.puts POWER.generate_nospecial(1 << 200, 100)
  f.puts
end
