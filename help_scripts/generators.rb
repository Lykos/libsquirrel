module Generators

  class DataColumn

    def initialize(type, name)
      @type = type
      @name = name
    end

    attr_reader :name

    def construct(element)
      case @type
      when :LongInt then "LongInt(\"#{element}\")"
      when :bool then element ? "true" : "false"
      when :qlonglong then "qlonglong(#{element})"
      when :string then "std::string(\"#{element}\")"
      when :int then element.to_s
      else
        raise "Unknown type #{type}"
      end
    end

    def typename
      if @type == :string
        "std::string"
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

    def to_s
      "QCOMPARE(#{@actual}, #{@expected});"
    end

  end

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
      join_indent(fetching) + "\n" + start_timer + join_indent(construction) + "\n" + join_indent(bla_tests) + end_timer
    end

    def start_timer
      ""
    end

    def end_timer
      ""
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

    def result(element)
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

    def result(element)
      element >= 0
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
               "std::string string_output = oss.str();"]
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
      [Test.new("constructed = input", "input"),
       Test.new("constructed", "input"),
       Test.new("constructed = constructed", "input"),
       Test.new("constructed", "input")] + super
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
      [Test.new("left.compareTo(right)", "result"),
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

  HEADER = <<EOS
#include "longinttest.h"
#include <sstream>
#include <cstring>
#include <QString>
#include <iostream>

using namespace DataStructures;

typedef LongInt::part_type part_type;
Q_DECLARE_METATYPE(DataStructures::LongInt)
Q_DECLARE_METATYPE(std::string)

EOS

  FIXED_TESTS = <<EOS
void LongIntTest::test_empty_constructor()
{
  QCOMPARE(LongInt(), LongInt(0));
}

EOS

  DEFAULT_CONSTRUCTOR = DefaultConstructorGenerator.new("default_constructor")

  COPY_CONSTRUCTOR = CopyConstructorGenerator.new("copy_constructor")

  STRING_CONSTRUCTOR = StringConstructorGenerator.new("string_constructor")

  ASSIGN = AssignGenerator.new("assign")

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

  MODULO = BinaryGenerator.new("modulo", "%")

  DIVIDED = BinaryGenerator.new("divided", "/")

  POWER = PowerGenerator.new("pow", "**", 1)

end