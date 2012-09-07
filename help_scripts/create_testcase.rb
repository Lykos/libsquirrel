#!/usr/bin/env ruby

$:.unshift(File.dirname(__FILE__))

require 'generators'

include Generators

N = 1

File.open(File.join(File.dirname(__FILE__), '..', 'TestDataStructures', 'longinttest.h'), 'w') do |h|
  File.open(File.join(File.dirname(__FILE__), '..', 'TestDataStructures', 'longinttest.cpp'), 'w') do |cpp|
    cpp.puts CPP_HEADER
    h.puts H_HEADER

    FIXED_HEADERS.each do |t|
      h.puts t
      h.puts
    end

    FIXED_TESTS.each do |t|
      cpp.puts t
      cpp.puts
    end

    (PRIMITIVE_CONSTRUCTORS + PRIMITIVE_CONVERSIONS).each_with_index do |generator, i|
      i %= PRIMITIVE_LENGTHS.length
      cpp.puts generator.generate(N, [-1, 1], [1 << PRIMITIVE_LENGTHS[i] / 2 - 1, 1 << PRIMITIVE_LENGTHS[i] - 1], [0, 1, 2])
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    (UNSIGNED_PRIMITIVE_CONSTRUCTORS + UNSIGNED_PRIMITIVE_CONVERSIONS).each_with_index do |generator, i|
      i %= PRIMITIVE_LENGTHS.length
      cpp.puts generator.generate(N, [1], [1 << PRIMITIVE_LENGTHS[i] / 2, 1 << PRIMITIVE_LENGTHS[i]], [0, 1, 2])
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    [
     COPY_CONSTRUCTOR,
     DECIMAL_STRING_CONSTRUCTOR,
     HEX_STRING_CONSTRUCTOR,
     DECIMAL_ISTREAM,
     HEX_ISTREAM,
     DECIMAL_OSTREAM,
     HEX_OSTREAM,
     ASSIGN,
     INC,
     DEC,
     UNARY_PLUS,
     UNARY_MINUS,
     BIT_NEGATE
    ].each do |generator|
      cpp.puts generator.generate(N, [-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
      cpp.puts
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    [RIGHT_SHIFT, LEFT_SHIFT].each do |generator|
      cpp.puts generator.generate(N, [-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2, 32])
      cpp.puts
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    [PLUS, MINUS, TIMES, COMPARE, BIT_OR, BIT_XOR, BIT_AND].each do |generator|
      cpp.puts generator.generate(N, [-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [0, 1, 2])
      cpp.puts
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    [MODULO, DIVIDED].each do |generator|
      cpp.puts generator.generate(N, [-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
      cpp.puts
      h.puts generator.test_method_header
      h.puts
      h.puts generator.data_method_header
      h.puts
    end

    cpp.puts POWER.generate(1, [-1, 1], [1], [200, 1 << 100], [100], [0, 1, 2], [0, 1, 2])
    cpp.puts
    h.puts POWER.test_method_header
    h.puts
    h.puts POWER.data_method_header
    h.puts

    cpp.puts CPP_FOOTER
    h.puts H_FOOTER
  end
end
