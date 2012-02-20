#!/usr/bin/env ruby

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
QTest::addColumn<LongInt>("element");
QTest::addColumn<LongInt>("result");

EOS
  end
  
  def footer
    @footer ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
QFETCH(LongInt, element);
QFETCH(LongInt, result);
LongInt copy (element);

QCOMPARE(#{@operator}element, result);
QCOMPARE(element, copy);
}
EOS
  end
  
  def evaluate(element)
    eval("#{@operator}#{element}")
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
    "QTest::newRow(\"#{title(element)}\")#{sep}<< #{element2}#{sep}<< #{result2};\n"
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
QFETCH(LongInt, element);
QFETCH(LongInt, result);
LongInt copy (element);

QCOMPARE(element#{@operator}#{@operator}, copy);
QCOMPARE(element, result);
QCOMPARE(#{@operator}#{@operator}copy, result);
QCOMPARE(copy, result);
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
QTest::addColumn<#{@type}>("input");
QTest::addColumn<bool>("sign");

EOS
  end
  
  def footer
    @footer1 ||= <<EOS
}

void LongIntTest::test_#{@name}()
{
QFETCH(#{@type}, input);
QFETCH(bool, sign);
EOS
    @footer ||= @footer1 + evaluation + "QCOMPARE(constructed.is_positive(), sign);\n\}\n"
  end
  
  def title(element)
    element
  end
  
  def line(element)
    sep = element.to_s.length > 50 ? "\n" : " "
    "QTest::newRow(\"#{title(element)}\")#{sep}<< #{construct(element)} << #{element >= 0 ? true : false};\n"
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
LongInt constructed (input);

std::ostringstream oss1;
oss1 << constructed;
std::ostringstream oss2;
oss2 << input;
QCOMPARE(oss1.str(), oss2.str());
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
LongInt constructed (input);

QCOMPARE(constructed, input);
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
LongInt constructed (input);

std::ostringstream oss;
oss << constructed;
QCOMPARE(oss.str(), input);
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
LongInt constructed;

QCOMPARE(constructed = input, input);
QCOMPARE(constructed, input);
QCOMPARE(constructed = constructed, input);
QCOMPARE(constructed, input);
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
QTest::addColumn<#{left_type}>("left");
QTest::addColumn<#{right_type}>("right");
QTest::addColumn<#{result_type}>("result");

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
QFETCH(#{left_type}, left);
QFETCH(#{right_type}, right);
QFETCH(#{result_type}, result);
EOS
    @footer ||= @footer2 + "\n" + evaluation
  end

  def evaluation
    <<EOS
LongInt copy (left);
QCOMPARE(left #{@operator} right, result);
QCOMPARE(left, copy);
copy #{@operator}= right;
QCOMPARE(copy, result);
}
EOS
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
    eval("#{left} #{@operator} #{right}")
  end
  
  def line(left, right)
    sep1 = left.to_s.length > 50 ? "\n" : " "
    sep2 = right.to_s.length > 50 ? "\n" : " "
    title = title(left, right)
    result = evaluate(left, right)
    left2 = construct_left(left)
    right2 = construct_right(right)
    result2 = construct_result(result)
    "QTest::newRow(\"#{title}\")#{sep1}<< #{left2}#{sep1}<< #{right2}#{sep2}<< #{result2};\n"
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
    double_foreach(limits1, limits2) do |limit1, limit2|
      double_foreach(signs1, signs2) do |sign1, sign2|
        cases += generate_n_random(sign1, sign2, limit1, limit2)
      end
    end
    # A little complicated because we don't want to have duplicates for 0 because of signs
    a_0 = special1.delete(0)
    b_0 = special2.delete(0)
    double_foreach(signs1, signs2) do |sign1, sign2|
      first = true
      special1.each do |a|
        if b_0
          cases += line(sign1 * a, 0)
        end
        special2.each do |b|
          cases += line(sign1 * a, sign2 * b)
          if a_0 && first
            cases += line(0, sign2 * b)
          end
        end
      first = false
      end
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

class CompareToGenerator < BinaryGenerator

  def result_type
    "int"
  end
  
  def construct_result(result)
    result.to_s
  end
    
  def evaluation
    <<EOS
bool larger = false, larger_equal = false, equal = false, smaller_equal = false, smaller = false, unequal = true;
if (result == 1) {
  larger = true;
  larger_equal = true;
} else if (result == 0) {
  larger_equal = true;
  equal = true;
  smaller_equal = true;
  unequal = false;
} else if (result == -1) {
  smaller_equal = true;
  smaller = true;
} else {
  QFAIL("Invalid result.");
}
QCOMPARE(left.compareTo(right), result);
QCOMPARE(left > right, larger);
QCOMPARE(left >= right, larger_equal);
QCOMPARE(left == right, equal);
QCOMPARE(left <= right, smaller_equal);
QCOMPARE(left < right, smaller);
QCOMPARE(left != right, unequal);
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
  puts generator.generate([-1, 1], [1], [200, 1 << 200], [200], [0, 1, 2], [0, 1, 2])
  puts
end

[
 BinaryGenerator.new("plus", "+"),
 BinaryGenerator.new("minus", "-"),
 BinaryGenerator.new("times", "*"),
 CompareToGenerator.new("compare_to", "<=>")
].each do |generator|
  puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [0, 1, 2])
  puts
end

generator = BinaryGenerator.new("modulo", "%")
puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 200], [0, 1, 2], [1, 2])
puts

generator = ShiftGenerator.new("divided", "/")
puts generator.generate([-1, 1], [-1, 1], [200, 1 << 200], [200, 1 << 31], [0, 1, 2], [1, 2])
puts

