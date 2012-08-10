#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'

include Generators

File.open(File.join(File.dirname(__FILE__), '..', 'TestDataStructures', 'longinttest.cpp'), 'w') do |f|
  f.puts HEADER
  f.puts FIXED_TESTS

  f.puts DEFAULT_CONSTRUCTOR.generate([-1, 1], [200, 1 << 33, 1 << 63], [0, 1, 2])
  f.puts

  [COPY_CONSTRUCTOR, STRING_CONSTRUCTOR, ASSIGN].each do |generator|
    f.puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
    f.puts
  end

  [INC, DEC].each do |generator|
    f.puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
    f.puts
  end

  [UNARY_PLUS, UNARY_MINUS].each do |generator|
    f.puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
    f.puts
  end

  [RIGHT_SHIFT, LEFT_SHIFT].each do |generator|
    f.puts generator.generate([-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2, 32])
    f.puts
  end

  [PLUS, MINUS, TIMES, COMPARE].each do |generator|
    f.puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [0, 1, 2])
    f.puts
  end

  [MODULO, DIVIDED].each do |generator|
    f.puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
    f.puts
  end

  f.puts POWER.generate([-1, 1], [1], [200, 1 << 100], [100], [0, 1, 2], [0, 1, 2])
  f.puts
end
