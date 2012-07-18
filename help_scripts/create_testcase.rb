#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'

include Generators

puts HEADER

puts DEFAULT_CONSTRUCTOR.generate([-1, 1], [200, 1 << 33, 1 << 63], [0, 1, 2])
puts
                    
[COPY_CONSTRUCTOR, STRING_CONSTRUCTOR, ASSIGN].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[INC, DEC].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[UNARY_PLUS, UNARY_MINUS].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[RIGHT_SHIFT, LEFT_SHIFT].each do |generator|
  puts generator.generate([-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2, 32])
  puts
end

[PLUS, MINUS, TIMES, COMPARE].each do |generator|
  puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [0, 1, 2])
  puts
end

[MODULO, DIVIDED].each do |generator|
  puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
  puts
end

puts POWER.generate([-1, 1], [1], [200, 1 << 100], [100], [0, 1, 2], [0, 1, 2])
puts
