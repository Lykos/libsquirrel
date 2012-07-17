#!/usr/bin/env ruby

INDENTATION = "  "

class CaseGenerator

  def initialize(name, number=2)
    @name = name
    @number = number
  end

  def generate_n_random(*args)
    cases = ""
    @number.times do
      cases += generate_random(*args)
    end
    cases
  end

  def construct_long_int(element)
    "LongInt(\"#{element}\")"
  end

end

class UnaryGenerator < CaseGenerator

  def initialize(name, operator, number=2)
    super(name, number)
    @operator = operator
  end

  def header
    @header ||= <<EOS
void LongIntTest::test_#{@name}_data()
{
#{INDENTATION}QTest::addColumn<LongInt>("element");
#{INDENTATION}QTest::addColumn<LongInt>("result");

EOS
  end

  def footer
    @footer ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
#{INDENTATION}QFETCH(LongInt, element);
#{INDENTATION}QFETCH(LongInt, result);
#{INDENTATION}LongInt copy (element);

#{INDENTATION}QCOMPARE(#{@operator}element, result);
#{INDENTATION}QCOMPARE(element, copy);
}
EOS
  end

  def evaluate(element)
    eval("#{@operator}(#{element})")
  end

  def construct_element(element)
    construct_long_int(element)
  end

  def construct_result(result)
    construct_long_int(result)
  end

  def title(element)
    "#{@operator}#{element}"
  end

  def line(element)
    result = evaluate(element)
    sep = element.to_s.length > 50 ? "\n" : " "
    element2 = construct_element(element)
    result2 = construct_result(result)
    "#{INDENTATION}QTest::newRow(\"#{title(element)}\")#{sep}<< #{element2}#{sep}<< #{result2};\n"
  end

  def generate_random(sign, limit)
    line(sign * (rand(limit) + 1))
  end

  def generate(signs, limits, special)
    cases = header
    limits.each do |limit|
      signs.each do |sign|
        cases += generate_n_random(sign, limit)
      end
    end
    a_0 = special.delete(0)
    if a_0
      cases += line(0)
    end
    signs.each do |sign|
      special.each do |a|
        cases += line(sign * a)
      end
    end
    cases + footer
  end

end

class IncDecGenerator < UnaryGenerator

  def footer
    @footer ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
#{INDENTATION}QFETCH(LongInt, element);
#{INDENTATION}QFETCH(LongInt, result);
#{INDENTATION}LongInt copy (element);

#{INDENTATION}QCOMPARE(element#{@operator}#{@operator}, copy);
#{INDENTATION}QCOMPARE(element, result);
#{INDENTATION}QCOMPARE(#{@operator}#{@operator}copy, result);
#{INDENTATION}QCOMPARE(copy, result);
}
EOS
  end

  def evaluate(element)
    eval("#{element} #{@operator} 1")
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

  def header
    @header ||= <<EOS
void LongIntTest::test_#{@name}_data()
{
#{INDENTATION}QTest::addColumn<#{@type}>("input");
#{INDENTATION}QTest::addColumn<bool>("sign");

EOS
  end

  def footer
    @footer1 ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
#{INDENTATION}QFETCH(#{@type}, input);
#{INDENTATION}QFETCH(bool, sign);
EOS
    @footer ||= @footer1 + evaluation + "QCOMPARE(constructed.is_positive(), sign);\n\}\n"
  end

  def title(element)
    element
  end

  def line(element)
    sep = element.to_s.length > 50 ? "\n" : " "
    "#{INDENTATION}QTest::newRow(\"#{title(element)}\")#{sep}<< #{construct(element)} << #{element >= 0 ? true : false};\n"
  end

end

class DefaultConstructorGenerator < ConstructorGenerator

  def initialize(name, number=2)
    super(name, "qlonglong", number)
  end

  def title(element)
    "LongInt(#{element})"
  end

  def construct(element)
    "qlonglong(#{element}l)"
  end

  def evaluation
    <<EOS
#{INDENTATION}LongInt constructed (input);

#{INDENTATION}std::ostringstream oss1;
#{INDENTATION}oss1 << constructed;
#{INDENTATION}std::ostringstream oss2;
#{INDENTATION}oss2 << input;
#{INDENTATION}QCOMPARE(oss1.str(), oss2.str());
EOS
  end

end

class CopyConstructorGenerator < ConstructorGenerator

  def initialize(name, number=2)
    super(name, "LongInt", number)
  end

  def title(element)
    "LongInt(LongInt(\\\"#{element}\\\"))"
  end

  def construct(element)
    construct_long_int(element)
  end

  def evaluation
    <<EOS
#{INDENTATION}LongInt constructed (input);

#{INDENTATION}QCOMPARE(constructed, input);
EOS
  end

end

class StringConstructorGenerator < ConstructorGenerator

  def initialize(name, number=2)
    super(name, "std::string", number)
  end

  def title(element)
    "LongInt(\\\"#{element}\\\")"
  end

  def construct(element)
    "std::string(\"#{element}\")"
  end

  def evaluation
    <<EOS
#{INDENTATION}LongInt constructed (input);

#{INDENTATION}std::ostringstream oss;
#{INDENTATION}oss << constructed;
#{INDENTATION}QCOMPARE(oss.str(), input);
EOS
  end

end

class AssignGenerator < CopyConstructorGenerator

  def initialize(name, number=2)
    super(name, number)
  end

  def title(element)
    "i = LongInt(\\\"#{element}\\\")"
  end

  def evaluation
    <<EOS
#{INDENTATION}LongInt constructed;

#{INDENTATION}QCOMPARE(constructed = input, input);
#{INDENTATION}QCOMPARE(constructed, input);
#{INDENTATION}QCOMPARE(constructed = constructed, input);
#{INDENTATION}QCOMPARE(constructed, input);
EOS
  end

end

class BinaryGenerator < CaseGenerator

  def initialize(name, operator, number=2)
    super(name, number)
    @operator = operator
  end

  def header
    <<EOS
void LongIntTest::test_#{@name}_data()
{
#{INDENTATION}QTest::addColumn<#{left_type}>("left");
#{INDENTATION}QTest::addColumn<#{right_type}>("right");
#{INDENTATION}QTest::addColumn<#{result_type}>("result");

EOS
  end

  def left_type
    "LongInt"
  end

  def right_type
    "LongInt"
  end

  def result_type
    "LongInt"
  end

  def footer
    @footer2 ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
#{INDENTATION}QFETCH(#{left_type}, left);
#{INDENTATION}QFETCH(#{right_type}, right);
#{INDENTATION}QFETCH(#{result_type}, result);
EOS
    @footer ||= @footer2 + "\n" + evaluation
  end

  def evaluation
    <<EOS
#{INDENTATION}LongInt copy (left);
#{INDENTATION}QCOMPARE(#{bin_op("left", "right")}, result);
#{INDENTATION}QCOMPARE(left, copy);
#{INDENTATION}#{bin_op_eq("copy", "right")};
#{INDENTATION}QCOMPARE(copy, result);
}
EOS
  end

  def bin_op(left, right)
    "#{left} #{@operator} #{right}"
  end

  def bin_op_eq(left, right)
    "#{left} #{@operator}= #{right}"
  end

  def construct_left(left)
    construct_long_int(left)
  end

  def construct_right(right)
    construct_long_int(right)
  end

  def construct_result(result)
    construct_long_int(result)
  end

  def title(left, right)
    "#{left} #{@operator} #{right}"
  end

  def evaluate(left, right)
    eval("(#{left}) #{@operator} (#{right})")
  end

  def line(left, right)
    sep1 = left.to_s.length > 50 ? "\n" : " "
    sep2 = right.to_s.length > 50 ? "\n" : " "
    title = title(left, right)
    result = evaluate(left, right)
    left2 = construct_left(left)
    right2 = construct_right(right)
    result2 = construct_result(result)
    "#{INDENTATION}QTest::newRow(\"#{title}\")#{sep1}<< #{left2}#{sep1}<< #{right2}#{sep2}<< #{result2};\n"
  end

  def generate_random(sign1, sign2, limit1, limit2, b_is_long=true)
    line(sign1 * (rand(limit1) + 1), sign2 * (rand(limit2) + 1))
  end

  def double_foreach(as, bs, &block)
    as.each do |a|
      bs.each do |b|
        yield a, b
      end
    end
  end

  def generate(signs1, signs2, limits1, limits2, special1, special2)
    cases = header
    double_foreach(signs1, signs2) do |sign1, sign2|
      double_foreach(limits1, limits2) do |limit1, limit2|
        cases += generate_n_random(sign1, sign2, limit1, limit2)
      end
    end
    # A little complicated because we don't want to have duplicates for 0 because of signs
    spec1_0 = special1.delete(0)
    spec2_0 = special2.delete(0)
    # special random cases
    double_foreach(signs1, special1) do |sign1, a|
      double_foreach(signs2, limits2) do |sign2, limit2|
        @number.times do
          cases += line(sign1 * a, sign2 * (rand(limit2) + 1))
        end
      end
    end
    # random special cases
    double_foreach(signs1, limits1) do |sign1, limit1|
      double_foreach(signs2, special2) do |sign2, b|
        @number.times do
          cases += line(sign1 * (rand(limit1) + 1), b)
        end
      end
    end
    # random zero cases
    if spec2_0
      double_foreach(signs1, limits1) do |sign1, limit1|
        @number.times do
          cases += line(sign1 * (rand(limit1) + 1), 0)
        end
      end
    end
    # zero random cases
    if spec1_0
      double_foreach(signs2, limits2) do |sign2, limit2|
        @number.times do
          cases += line(0, sign2 * (rand(limit2) + 1))
        end
      end
    end
    # special special cases
    double_foreach(signs1, special1) do |sign1, a|
      double_foreach(signs2, special2) do |sign2, b|
        cases += line(sign1 * a, sign2 * b)
      end
    end
    # zero special cases
    if spec1_0
      double_foreach(signs2, special2) do |sign2, b|
        cases += line(0, sign2 * b)
      end
    end
    # special zero cases
    if spec2_0
      double_foreach(signs1, special1) do |sign1, a|
        cases += line(sign1 * a, 0)
      end
    end
    # zero zero case
    if spec1_0 && spec2_0
      cases += line(0, 0)
    end
    cases + footer
  end
end

class ShiftGenerator < BinaryGenerator

  def construct_right(right)
    right.to_s
  end

  def right_type
    "int"
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
    "int"
  end

  def construct_result(result)
    result.to_s
  end

  def evaluation
    <<EOS
#{INDENTATION}bool larger = false, larger_equal = false, equal = false, smaller_equal = false, smaller = false, unequal = true;
#{INDENTATION}if (result == 1) {
#{INDENTATION}#{INDENTATION}larger = true;
#{INDENTATION}#{INDENTATION}larger_equal = true;
#{INDENTATION}} else if (result == 0) {
#{INDENTATION}#{INDENTATION}larger_equal = true;
#{INDENTATION}#{INDENTATION}equal = true;
#{INDENTATION}#{INDENTATION}smaller_equal = true;
#{INDENTATION}#{INDENTATION}unequal = false;
#{INDENTATION}} else if (result == -1) {
#{INDENTATION}#{INDENTATION}smaller_equal = true;
#{INDENTATION}#{INDENTATION}smaller = true;
#{INDENTATION}} else {
#{INDENTATION}#{INDENTATION}QFAIL("Invalid result.");
#{INDENTATION}}
#{INDENTATION}QCOMPARE(left.compareTo(right), result);
#{INDENTATION}QCOMPARE(left > right, larger);
#{INDENTATION}QCOMPARE(left >= right, larger_equal);
#{INDENTATION}QCOMPARE(left == right, equal);
#{INDENTATION}QCOMPARE(left <= right, smaller_equal);
#{INDENTATION}QCOMPARE(left < right, smaller);
#{INDENTATION}QCOMPARE(left != right, unequal);
}
EOS
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
#{INDENTATINON}number = LongInt(5);
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
#{INDENTATION}if (half_size != 32) {
#{INDENTATION}#{INDENTATION}char str[200];
#{INDENTATION}#{INDENTATION}sprintf(str, "Half size is %d instead of the expected 32.",half_size);
#{INDENTATION}#{INDENTATION}QWARN(str);
#{INDENTATION}}
#{INDENTATION}QCOMPARE((int) lower_half(int1), lower);
#{INDENTATION}QCOMPARE((int) lower_half(number3), 0);
#{INDENTATION}QCOMPARE((int) lower_half(0), 0);
#{INDENTATION}QCOMPARE((int) lower_half((1l << half_size) + 2), 2);
#{INDENTATION}QCOMPARE((int) lower_half(number2), (int) number2);
#{INDENTATION}QCOMPARE((int) lower_half(number2 << 1), 11 << 1);
}

void LongIntTest::test_upper_half()
{
#{INDENTATION}QCOMPARE((int) upper_half(int2), upper);
#{INDENTATION}QCOMPARE((int) upper_half(number3), 1835008);
#{INDENTATION}QCOMPARE((int) upper_half(number2 << half_size), (int) number2);
#{INDENTATION}QCOMPARE((int) upper_half(number2 << 1), 1);
#{INDENTATION}QCOMPARE((int) upper_half(number2), 0);
#{INDENTATION}QCOMPARE((int) upper_half(0), 0);
}

void LongIntTest::test_empty_constructor()
{
#{INDENTATION}QCOMPARE(LongInt(), LongInt(0));
}

// Auto generated
EOS

puts header

generator = DefaultConstructorGenerator.new("default_constructor")
puts generator.generate([-1, 1], [200, 1 << 33, 1 << 63], [0, 1, 2, -1 << 63])
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
puts generator.generate([-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2])
puts
