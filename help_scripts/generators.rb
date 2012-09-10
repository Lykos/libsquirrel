module Generators

  class DataColumn

    def initialize(type, name)
      @type = type
      @name = name
    end

    attr_reader :name

    def construct(element)
      case @type
      when :LongInt then sprintf("%s0x%x_long", element >= 0 ? "" : "-", element.abs)
      when :bool then element ? "true" : "false"
      when :qlonglong then sprintf("qlonglong(%s0x%x)", element >= 0 ? "" : "-", element.abs)
      when :string then "string(\"#{element}\")"
      when :hex_string then sprintf("string(\"%s0x%x\")", element >= 0 ? "" : "-", element.abs)
      when :no0x_hex_string then sprintf("string(\"%s%x\")", element >= 0 ? "" : "-", element.abs)
      when :int then element.to_s
      else
        raise "Unknown type #{@type}"
      end
    end

    def escaped_construct(element)
      construct(element).gsub("\"", "\\\"")
    end

    def typename
      if @type == :hex_string
        "string"
      elsif @type == :no0x_hex_string
        "string"
      else
        @type.to_s
      end
    end

  end

  class Test

    def initialize(actual, expected)
      @actual = actual
      @expected = expected
    end

    attr_reader :actual, :expected

    def compare_macro
      "QCOMPARE"
    end

    def to_s
      compare_macro + "(#{@actual}, #{@expected});"
    end

  end

  class IntTest < Test

    def initialize(actual, expected)
      super(actual, expected)
    end

    def compare_macro
      "COMPARE_INTS"
    end

  end

  class CaseGenerator

    INDENTATION = "  "
    NEWLINE_SIZE = 50

    def initialize(name)
      @name = name
    end

    attr_reader :name

    def generate_n_random(n, *args)
      cases = []
      n.times do
        cases.push(generate_random(*args))
      end
      cases
    end

    def join_indent(lines)
      # ignore empty lines
      lines.select { |l| !(l =~ /^\s*$/) }.collect { |l| INDENTATION + l + "\n" }.join
    end

    def data_method_signature
      "void LongIntTest::test_#{@name}_data()"
    end

    def data_method_header
      INDENTATION + "void test_#{@name}_data();"
    end

    def test_method_header
      INDENTATION + "void test_#{@name}();"
    end

    def test_method_signature
      "void LongIntTest::test_#{@name}()"
    end

    def fetching
      data_columns.collect { |c| "QFETCH(#{c.typename}, #{c.name});" }
    end

    def column_declarations
      data_columns.collect { |c| "QTest::addColumn<#{c.typename}>(\"#{c.name}\");" }
    end

    def data_method_body(*args)
      join_indent(column_declarations) + "\n" + join_indent(generate_cases(*args))
    end

    def test_method_body
      bla_tests = tests.collect { |c| c.to_s}
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

    def initialize(name, operator)
      super(name)
      @operator = operator
    end

    def data_columns
      [DataColumn.new(:LongInt, "element"), DataColumn.new(:LongInt, "result")]
    end

    def construction
      ["LongInt copy (element);"]
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

    def generate_cases(n, signs, limits, special)
      cases = []
      if special.delete(0)
        cases.push(line(0))
      end

      double_foreach(signs, special) do |sign, a|
        cases.push(line(sign * a))
      end

      double_foreach(limits, signs) do |limit, sign|
        cases += generate_n_random(n, sign, limit)
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

    def result(element)
      eval("(#{element}) #{@operator} 1")
    end

    def title(element)
      "#{element}#{@operator}#{@operator}"
    end

  end

  class OStreamGenerator < UnaryGenerator

    def initialize(name, type)
      super(name, "")
      @type = type
    end

    def data_columns
      [DataColumn.new(:LongInt, "number"),
       DataColumn.new(@type, "result")]
     end

    def result(element)
      element
    end

    def construction
      ["ostringstream oss;",
       "oss << number;",
       "string string_result = oss.str();"]
    end

    def tests
      [Test.new("string_result", "result")]
    end

  end

  class DecimalOStreamGenerator < OStreamGenerator

    def initialize
      super("decimal_ostream", :string)
    end

    def title(element)
      "out << #{data_columns[0].escaped_construct(element)}"
    end

  end

  class HexOStreamGenerator < OStreamGenerator

    def initialize
      super("hex_ostream", :no0x_hex_string)
    end

    def construction
      super.insert(1, "oss.flags(ios_base::hex);")
    end

    def title(element)
      "out << hex << #{data_columns[0].escaped_construct(element)}"
    end

  end

  class PrimitiveConversionGenerator < UnaryGenerator

    def initialize(type)
      super(type.gsub(" ", "_") + "_conversion", "(#{type})")
      @type = type
    end

    def result(element)
      element
    end

    def tests
      [IntTest.new(super[0].actual, super[0].expected),
       super[1]]
    end

    def data_columns
      [DataColumn.new(:LongInt, "element"),
       DataColumn.new(:qlonglong, "result")]
    end

  end

  class ConstructorGenerator < UnaryGenerator

    def initialize(name, type)
      super(name, "")
      @type = type
    end

    def result(element)
      element
    end

    def data_columns
      [DataColumn.new(@type, "input"),
       DataColumn.new(:LongInt, "result")]
    end

    def construction
      ["LongInt constructed (input);"]
    end

    def tests
      [Test.new("constructed", "result")]
    end

    def title(element)
      "LongInt(#{data_columns[0].escaped_construct(element)})"
    end

  end

  class PrimitiveConstructorGenerator < ConstructorGenerator

    def initialize(type)
      super(type.gsub(" ", "_") + "_constructor", :qlonglong)
      @int_type = type
    end

    def construction
      ["LongInt constructed ((#{@int_type})input);"]
    end

    def title(element)
      "LongInt(#{element})"
    end

  end

  class DecimalStringConstructorGenerator < ConstructorGenerator

    def initialize
      super("string_constructor", :string)
    end

    def title(element)
      "LongInt(\\\"#{element}\\\")"
    end

  end

  class HexStringConstructorGenerator < ConstructorGenerator

    def initialize
      super("hex_string_constructor", :hex_string)
    end

    def title(element)
      sprintf("LongInt(\\\"%s0x%x\\\")", element >= 0 ? "" : "-", element.abs)
    end

  end

  class AssignGenerator < ConstructorGenerator

    def initialize
      super("assign", :LongInt)
    end

    def title(element)
      "i = #{data_columns[0].escaped_construct(element)}"
    end

    def construction
      ["LongInt constructed;"]
    end

    def tests
      [Test.new("constructed = input", "input"),
       Test.new("constructed", "input"),
       Test.new("constructed = constructed", "input"),
       Test.new("constructed", "input")] + super
    end

  end

  class IStreamGenerator < ConstructorGenerator

    def initialize(name, type)
      super(name, type)
    end

    def construction
      ["LongInt constructed;",
       "istringstream iss (input);",
       "iss >> constructed;"]
    end

  end

  class DecimalIStreamGenerator < IStreamGenerator

    def initialize
      super("decimal_istream", :string)
    end

    def title(element)
      "istream(\\\"#{element}\\\") >> constructed"
    end

  end

  class HexIStreamGenerator < IStreamGenerator

    def initialize
      super("hex_istream", :no0x_hex_string)
    end

    def construction
      super.insert(2, "iss.flags(ios_base::hex);")
    end

    def title(element)
      "istream(\\\"#{element}\\\") >> hex >> constructed"
    end

  end

  class BinaryGenerator < CaseGenerator

    def initialize(name, operator)
      super(name)
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

    def generate_cases(n, signs1, signs2, limits1, limits2, special1, special2)
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
          n.times do
            cases.push(line(sign1 * (rand(limit1) + 1), 0))
          end
        end
      end

      # zero random cases
      if spec1_0
        double_foreach(signs2, limits2) do |sign2, limit2|
          n.times do
            cases.push(line(0, sign2 * (rand(limit2) + 1)))
          end
        end
      end

      # random special cases
      quadruple_foreach(signs1, limits1, signs2, special2) do |sign1, limit1, sign2, b|
        n.times do
          cases.push(line(sign1 * (rand(limit1) + 1), b))
        end
      end

      # special random cases
      quadruple_foreach(signs1, special1, signs2, limits2) do |sign1, a, sign2, limit2|
        n.times do
          cases.push(line(sign1 * a, sign2 * (rand(limit2) + 1)))
        end
      end

      # random random cases
      quadruple_foreach(signs1, limits1, signs2, limits2) do |sign1, limit1, sign2, limit2|
        cases += generate_n_random(n, sign1, sign2, limit1, limit2)
      end

      cases
    end

  end

  class DividedGenerator < BinaryGenerator

    def line(a, b)
      if b == 0
        "// " + super
      else
        super
      end
    end

    def sign(a)
      a <=> 0
    end

    def result(a, b)
      sign(a) * sign(b) * (a.abs / b.abs)
    end

  end

  class ModuloGenerator < DividedGenerator

    def result(a, b)
      sign(a) * (a.abs % b.abs)
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
               "LongInt copy_left (left), copy_right (right);",
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
      [IntTest.new("left.compare_to(right)", "result"),
       Test.new("left > right", "larger"),
       Test.new("left >= right", "larger_equal"),
       Test.new("left == right", "equal"),
       Test.new("left <= right", "smaller_equal"),
       Test.new("left < right", "smaller"),
       Test.new("left != right", "unequal"),
       Test.new("left", "copy_left"),
       Test.new("right", "copy_right")]
    end

  end

  CPP_HEADER = <<EOS
#include "longinttest.h"
#include "DataStructures/longint.h"
#include "comparemacros.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace DataStructures;
using namespace std;

typedef LongInt::part_type part_type;
Q_DECLARE_METATYPE(LongInt)
Q_DECLARE_METATYPE(string)

EOS

  FIXED_HEADERS = [CaseGenerator::INDENTATION + "void test_empty_constructor();"]

  FIXED_TESTS = [<<EOS
void LongIntTest::test_empty_constructor()
{
  QCOMPARE(LongInt(), LongInt(0));
}
EOS
]

  H_HEADER = <<EOS
#ifndef LONGINTTEST_H
#define LONGINTTEST_H
#include <QtTest/QtTest>

class LongIntTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
EOS

  H_FOOTER = <<EOS
};

#endif // LONGINTTEST_H
EOS

  CPP_FOOTER = ""

  raise if FIXED_HEADERS.length != FIXED_TESTS.length

  PRIMITIVE_TYPES = ["char", "short", "int", "long int", "long long int"]

  PRIMITIVE_LENGTHS = [8, 16, 32, 64, 64]

  BOOL_CONSTRUCTOR = PrimitiveConstructorGenerator.new("bool")

  BOOL_CONVERSION = PrimitiveConversionGenerator.new("bool")

  PRIMITIVE_CONSTRUCTORS = PRIMITIVE_TYPES.collect do |type|
    PrimitiveConstructorGenerator.new(type)
  end

  UNSIGNED_PRIMITIVE_CONSTRUCTORS = PRIMITIVE_TYPES.collect do |type|
    PrimitiveConstructorGenerator.new("unsigned #{type}")
  end

  PRIMITIVE_CONVERSIONS = PRIMITIVE_TYPES.collect do |type|
    PrimitiveConversionGenerator.new(type)
  end

  UNSIGNED_PRIMITIVE_CONVERSIONS = PRIMITIVE_TYPES.collect do |type|
    PrimitiveConversionGenerator.new("unsigned #{type}")
  end

  COPY_CONSTRUCTOR = ConstructorGenerator.new("copy_constructor", :LongInt)

  DECIMAL_STRING_CONSTRUCTOR = DecimalStringConstructorGenerator.new

  HEX_STRING_CONSTRUCTOR = HexStringConstructorGenerator.new

  DECIMAL_ISTREAM = DecimalIStreamGenerator.new

  HEX_ISTREAM = HexIStreamGenerator.new

  DECIMAL_OSTREAM = DecimalOStreamGenerator.new

  HEX_OSTREAM = HexOStreamGenerator.new

  ASSIGN = AssignGenerator.new

  INC = IncDecGenerator.new("inc", "+")

  DEC = IncDecGenerator.new("dec", "-")

  UNARY_PLUS = UnaryGenerator.new("unary_plus", "+")

  UNARY_MINUS = UnaryGenerator.new("unary_minus", "-")

  BIT_NEGATE = UnaryGenerator.new("bit_negate", "~")

  LEFT_SHIFT = ShiftGenerator.new("left_shift", "<<")

  RIGHT_SHIFT = ShiftGenerator.new("right_shift", ">>")

  PLUS = BinaryGenerator.new("plus", "+")

  MINUS = BinaryGenerator.new("minus", "-")

  TIMES = BinaryGenerator.new("times", "*")

  COMPARE = CompareToGenerator.new("compare_to", "<=>")

  BIT_OR = BinaryGenerator.new("bit_or", "|")

  BIT_XOR = BinaryGenerator.new("bit_xor", "^")

  BIT_AND = BinaryGenerator.new("bit_and", "&")

  MODULO = ModuloGenerator.new("modulo", "%")

  DIVIDED = DividedGenerator.new("divided", "/")

  POWER = PowerGenerator.new("pow", "**")

end
