#!/usr/bin/env ruby

class DataColumn

  def initialize(type, name)
    @type = type
    @name = name
  end

  attr_reader :type, :name

  def construct(element)
    case @type
    when :LongInt then "LongInt(\"#{element}\")"
    when :bool then  element.to_s
    when :qlonglong then "qlonglong(#{element})"
    when :string then "std::string(\"#{element}\")"
    when :int then element.to_s
    else
      raise "Unknown type #{type}"
    end
  end

end

Test = Struct.new(:actual, :expected)

class CaseGenerator

  INDENTATION = "  "
  NEWLINE_SIZE = 50
  
  def initialize(name, number=2)
    @name = name
    @number = number
  end
  
  def generate_n_random(*args)
    cases = []
    @number.times do
      cases.push(generate_random(*args))
    end
    cases
  end

  def join_indent(lines)
    lines.collect { |l| INDENTATION + l + "\n" }.join
  end

  def data_method_signature
    "void LongIntTest::test_#{@name}_data()"
  end

  def test_method_signature
    "void LongIntTest::test_#{@name}"
  end

  def fetching
    data_columns.collect { |c| "QFETCH(#{c.type.to_s}, #{c.name})" }
  end

  def column_declarations
    data_columns.collect { |c| "QTest::addColumn<#{c.type.to_s}>(\"#{c.name}\");" }
  end
    
  def data_method_body(*args)
    join_indent(column_declarations) + "\n" + join_indent(generate_cases(*args))
  end

  def test_method_body
    bla_tests = tests.collect { |c| "QCOMPARE(#{c.actual}, #{c.expected});"}
    join_indent(fetching) + "\n" + join_indent(construction) + "\n" + join_indent(bla_tests)
  end

  def generate(*args)
    data_method_signature + "\n{\n" + data_method_body(*args) + "}\n\n" + test_method_signature + "\n{\n" + test_method_body + "}\n\n"
  end

  def whitespace(element)
    element.length > NEWLINE_SIZE ? "\n#{INDENTATION * 3}" : " "
  end

  def line(*args)
    s = "QTest::newRow(\"#{title(*args)}\")"
    raise "not the right number of arguments" unless args.length + 1 == data_columns.length
    args.push(result(*args))
    args.each_with_index do |arg, i|
      bla = data_columns[i].construct(arg)
      s += whitespace(bla) + "<< " + bla
    end
    s + ";"
  end
  
  def double_foreach(as, bs, &block)
    as.each do |a|
      bs.each do |b|
        yield a, b
      end
    end
  end

end

class UnaryGenerator < CaseGenerator
  
  def initialize(name, operator, number=2)
    super(name, number)
    @operator = operator
  end
  
  def data_columns
    [DataColumn.new(:LongInt, "element"), DataColumn.new(:LongInt, "result")]
  end
  
  def construction
    ["LongInt copy (element)"]
  end

  def tests
    [Test.new("#{@operator}element", "result"),
     Test.new("element", "copy")]
  end
   
  def result(element)
    eval("#{@operator}(#{element})")
  end  

  def title(element)
    "#{@operator}#{element}"
  end
  
  def generate_random(sign, limit)
    line(sign * (rand(limit) + 1))
  end
  
  def generate_cases(signs, limits, special)
    cases = []
    if special.delete(0)
      cases.push(line(0))
    end

    double_foreach(signs, special) do |sign, a|
      cases.push(line(sign * a))
    end

    double_foreach(limits, signs) do |limit, sign|
      cases += generate_n_random(sign, limit)
    end
    cases
  end
  
end

class IncDecGenerator < UnaryGenerator
  
  def tests
    [Test.new("element#{@operator}#{@operator}", "copy"),
     Test.new("element", "result"),
     Test.new("#{@operator}#{@operator}copy", "result"),
     Test.new("copy", "result")]
  end
  
  def evaluate(element)
    eval("(#{element}) #{@operator} 1")
  end
  
  def title(element)
    "#{element}#{@operator}#{@operator}"
  end
  
end


class ConstructorGenerator < UnaryGenerator
  
  def initialize(name, type, number=2)
    super(name, "", number)
    @type = type
  end
  
  def data_columns
    [DataColumn.new(@type, "input"),
     DataColumn.new(:bool, "sign")]
  end

  def construction
    ["LongInt constructed (input);"]
  end

  def tests
    [Test.new("constructed.is_positive()", "sign")]
  end
  
  def title(element)
    element.to_s
  end
  
end

class DefaultConstructorGenerator < ConstructorGenerator
  
  def initialize(name, number=2)
    super(name, :qlonglong, number)
  end

  def construction
    super + ["",
             "// We need this trick because normal comparing would use exactly this constructor to transform the integer into a LongInt.",
             "std::ostringstream oss1;",
             "oss1 << constructed;",
             "std::ostringstream oss2;",
             "oss2 << input;",
             "std::string actual_string = oss1.str();",
             "std::string expected_string = oss2.str();"]
  end

  def tests
    super + [Test.new("actual_string", "expected_string")]
  end

  def title(element)
    "LongInt(#{element})"
  end
  
end

class CopyConstructorGenerator < ConstructorGenerator
  
  def initialize(name, number=2)
    super(name, :LongInt, number)
  end
  
  def title(element)
    "LongInt(LongInt(\\\"#{element}\\\"))"
  end

  def construct(element)
    construct_long_int(element)
  end
  
  def tests
    super + [Test.new("constructed", "input")]
  end
  
end

class StringConstructorGenerator < ConstructorGenerator
  
  def initialize(name, number=2)
    super(name, :string, number)
  end
  
  def title(element)
    "LongInt(\\\"#{element}\\\")"
  end
  
  def construction
    super + ["std::ostringstream oss;",
             "oss << constructed;",
             "std::string string_output"]
  end

  def tests
    super + [Test.new("string_output", "input")]
  end

end

class AssignGenerator < CopyConstructorGenerator
  
  def initialize(name, number=2)
    super(name, number)
  end
  
  def title(element)
    "i = LongInt(\\\"#{element}\\\")"
  end
  
  def construction
    ["LongInt constructed;"]
  end

  def tests
    super + [Test.new("constructed = input", "input"),
             Test.new("constructed", "input"),
             Test.new("constructed = constructed", "input"),
             Test.new("constructed", "input")]
  end
  
end

class BinaryGenerator < CaseGenerator

  def initialize(name, operator, number=2)
    super(name, number)
    @operator = operator
  end
  
  def data_columns
    [DataColumn.new(left_type, "left"),
     DataColumn.new(right_type, "right"),
     DataColumn.new(result_type, "result")]
  end

  def left_type
    :LongInt
  end

  def right_type
    :LongInt
  end
  
  def result_type
    :LongInt
  end

  def construction
    ["LongInt copy (left);"]
  end

  def tests
    [Test.new(bin_op("left", "right"), "result"),
     Test.new("left", "copy"),
     Test.new(bin_op_eq("copy", "right"), "result"),
     Test.new("copy", "result")]
  end

  def bin_op(left, right)
    "#{left} #{@operator} #{right}"
  end

  def bin_op_eq(left, right)
    "#{left} #{@operator}= #{right}"
  end

  def title(left, right)
    "#{left} #{@operator} #{right}"
  end
  
  def result(left, right)
    eval("(#{left}) #{@operator} (#{right})")
  end

  def generate_random(sign1, sign2, limit1, limit2, b_is_long=true)
    line(sign1 * (rand(limit1) + 1), sign2 * (rand(limit2) + 1))
  end

  def quadruple_foreach(as, bs, cs, ds, &block)
    double_foreach(as, bs) do |a, b|
      double_foreach(cs, ds) do |c, d|
        yield a, b, c, d
      end
    end
  end
  
  def generate_cases(signs1, signs2, limits1, limits2, special1, special2)
    # A little complicated because we don't want to have duplicates for 0 because of signs
    spec1_0 = special1.delete(0)
    spec2_0 = special2.delete(0)

    cases = []
    # zero zero case
    if spec1_0 && spec2_0
      cases.push(line(0, 0))
    end

    # zero special cases
    if spec1_0
      double_foreach(signs2, special2) do |sign2, b|
        cases.push(line(0, sign2 * b))
      end
    end

    # special zero cases
    if spec2_0
      double_foreach(signs1, special1) do |sign1, a|
        cases.push(line(sign1 * a, 0))
      end
    end

    # special special cases
    quadruple_foreach(signs1, special1, signs2, special2) do |sign1, a, sign2, b|
      cases.push(line(sign1 * a, sign2 * b))
    end

    # random zero cases
    if spec2_0
      double_foreach(signs1, limits1) do |sign1, limit1|
        @number.times do
          cases.push(line(sign1 * (rand(limit1) + 1), 0))
        end
      end
    end

    # zero random cases
    if spec1_0
      double_foreach(signs2, limits2) do |sign2, limit2|
        @number.times do
          cases.push(line(0, sign2 * (rand(limit2) + 1)))
        end
      end
    end

    # random special cases
    quadruple_foreach(signs1, limits1, signs2, special2) do |sign1, limit1, sign2, b|
      @number.times do
        cases.push(line(sign1 * (rand(limit1) + 1), b))
      end
    end

    # special random cases
    quadruple_foreach(signs1, special1, signs2, limits2) do |sign1, a, sign2, limit2|
      @number.times do
        cases.push(line(sign1 * a, sign2 * (rand(limit2) + 1)))
      end
    end

    # random random cases
    quadruple_foreach(signs1, limits1, signs2, limits2) do |sign1, limit1, sign2, limit2|
      cases += generate_n_random(sign1, sign2, limit1, limit2)
     end

    cases
  end

end

class ShiftGenerator < BinaryGenerator

  def right_type
    :int
  end

end

class PowerGenerator < ShiftGenerator

  def bin_op(left, right)
    "#{left}.#{@name}(#{right})"
  end

  def bin_op_eq(left, right)
    "#{left}.#{@name}_eq(#{right})"
  end

end

class CompareToGenerator < BinaryGenerator

  def result_type
    :int
  end
  
  def construction
    super + ["bool larger = false, larger_equal = false, equal = false, smaller_equal = false, smaller = false, unequal = true;",
             "if (result == 1) {",
             "#{INDENTATION}larger = true;",
             "#{INDENTATION}larger_equal = true;",
             "} else if (result == 0) {",
             "#{INDENTATION}larger_equal = true;",
             "#{INDENTATION}equal = true;",
             "#{INDENTATION}smaller_equal = true;",
             "#{INDENTATION}unequal = false;",
             "} else if (result == -1) {",
             "#{INDENTATION}smaller_equal = true;",
             "#{INDENTATION}smaller = true;",
             "} else {",
             "#{INDENTATION}QFAIL(\"Invalid result.\");",
             "}"]
  end
    
  def tests
    super + [Test.new("left.compareTo(right)", "result"),
             Test.new("left > right", "larger"),
             Test.new("left >= right", "larger_equal"),
             Test.new("left == right", "equal"),
             Test.new("left <= right", "smaller_equal"),
             Test.new("left < right", "smaller"),
             Test.new("left != right", "unequal")]
  end
  
end

header = <<EOS
#include "longinttest.h"
#include <sstream>
#include <cstring>
#include <QString>
#include <iostream>

using namespace DataStructures;

typedef LongInt::part_type part_type;
Q_DECLARE_METATYPE(DataStructures::LongInt)
Q_DECLARE_METATYPE(std::string)

LongIntTest::LongIntTest()
{
}

void LongIntTest::init()
{
  number = LongInt(5);
}

static const int half_size = sizeof(part_type) / 2 * CHAR_BIT;
static const part_type int1 = 0x8f70e4b4db783331;
static const int lower = 0xdb783331;
static const part_type int2 = 0x3f7076c9145b28a0;
static const int upper = 0x3f7076c9;
static const part_type number2 = 11l + (1l << (half_size - 1));
static const part_type number3 = 7881299347898368l;

void LongIntTest::test_lower_half()
{
  if (half_size != 32) {
    char str[200];
    sprintf(str, "Half size is %d instead of the expected 32.",half_size);
    QWARN(str);
  }
  QCOMPARE((int) lower_half(int1), lower);
  QCOMPARE((int) lower_half(number3), 0);
  QCOMPARE((int) lower_half(0), 0);
  QCOMPARE((int) lower_half((1l << half_size) + 2), 2);
  QCOMPARE((int) lower_half(number2), (int) number2);
  QCOMPARE((int) lower_half(number2 << 1), 11 << 1);
}

void LongIntTest::test_upper_half()
{
  QCOMPARE((int) upper_half(int2), upper);
  QCOMPARE((int) upper_half(number3), 1835008);
  QCOMPARE((int) upper_half(number2 << half_size), (int) number2);
  QCOMPARE((int) upper_half(number2 << 1), 1);
  QCOMPARE((int) upper_half(number2), 0);
  QCOMPARE((int) upper_half(0), 0);
}

void LongIntTest::test_empty_constructor()
{
  QCOMPARE(LongInt(), LongInt(0));
}

// Auto generated
EOS

puts header

generator = DefaultConstructorGenerator.new("default_constructor")
puts generator.generate([-1, 1], [200, 1 << 33, 1 << 63], [0, 1, 2])
puts
                    
[           
 CopyConstructorGenerator.new("copy_constructor"),
 StringConstructorGenerator.new("string_constructor"),
 AssignGenerator.new("assign")
].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[
 IncDecGenerator.new("inc", "+"),
 IncDecGenerator.new("dec", "-")
].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[
 UnaryGenerator.new("unary_plus", "+"),
 UnaryGenerator.new("unary_minus", "-")
].each do |generator|
  puts generator.generate([-1, 1], [200, 1 << 33, 1 << 200], [0, 1, 2])
  puts
end

[
 ShiftGenerator.new("left_shift", "<<"),
 ShiftGenerator.new("right_shift", ">>")
].each do |generator|
  puts generator.generate([-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2, 32])
  puts
end

[
 BinaryGenerator.new("plus", "+"),
 BinaryGenerator.new("minus", "-"),
 BinaryGenerator.new("times", "*"),
 CompareToGenerator.new("compare_to", "<=>"),
 BinaryGenerator.new("bit_or", "|"),
 BinaryGenerator.new("bit_xor", "^"),
 BinaryGenerator.new("bit_and", "&")
].each do |generator|
  puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [0, 1, 2])
  puts
end

generator = BinaryGenerator.new("modulo", "%")
puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
puts

generator = BinaryGenerator.new("divided", "/")
puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
puts

generator = PowerGenerator.new("pow", "**", 1) { |a, b| a ** b }
puts generator.generate([-1, 1], [1], [200, 1 << 100], [100], [0, 1, 2], [0, 1, 2])
puts
