#ifndef LONGINTTEST_H
#define LONGINTTEST_H
#include <QtTest/QtTest>

class LongIntTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_empty_constructor();

  void test_char_constructor();

  void test_char_constructor_data();

  void test_short_constructor();

  void test_short_constructor_data();

  void test_int_constructor();

  void test_int_constructor_data();

  void test_long_int_constructor();

  void test_long_int_constructor_data();

  void test_long_long_int_constructor();

  void test_long_long_int_constructor_data();

  void test_char_conversion();

  void test_char_conversion_data();

  void test_short_conversion();

  void test_short_conversion_data();

  void test_int_conversion();

  void test_int_conversion_data();

  void test_long_int_conversion();

  void test_long_int_conversion_data();

  void test_long_long_int_conversion();

  void test_long_long_int_conversion_data();

  void test_unsigned_char_constructor();

  void test_unsigned_char_constructor_data();

  void test_unsigned_short_constructor();

  void test_unsigned_short_constructor_data();

  void test_unsigned_int_constructor();

  void test_unsigned_int_constructor_data();

  void test_unsigned_long_int_constructor();

  void test_unsigned_long_int_constructor_data();

  void test_unsigned_long_long_int_constructor();

  void test_unsigned_long_long_int_constructor_data();

  void test_unsigned_char_conversion();

  void test_unsigned_char_conversion_data();

  void test_unsigned_short_conversion();

  void test_unsigned_short_conversion_data();

  void test_unsigned_int_conversion();

  void test_unsigned_int_conversion_data();

  void test_unsigned_long_int_conversion();

  void test_unsigned_long_int_conversion_data();

  void test_unsigned_long_long_int_conversion();

  void test_unsigned_long_long_int_conversion_data();

  void test_copy_constructor();

  void test_copy_constructor_data();

  void test_string_constructor();

  void test_string_constructor_data();

  void test_hex_string_constructor();

  void test_hex_string_constructor_data();

  void test_decimal_istream();

  void test_decimal_istream_data();

  void test_hex_istream();

  void test_hex_istream_data();

  void test_decimal_ostream();

  void test_decimal_ostream_data();

  void test_hex_ostream();

  void test_hex_ostream_data();

  void test_assign();

  void test_assign_data();

  void test_inc();

  void test_inc_data();

  void test_dec();

  void test_dec_data();

  void test_unary_plus();

  void test_unary_plus_data();

  void test_unary_minus();

  void test_unary_minus_data();

  void test_bit_negate();

  void test_bit_negate_data();

  void test_right_shift();

  void test_right_shift_data();

  void test_left_shift();

  void test_left_shift_data();

  void test_plus();

  void test_plus_data();

  void test_minus();

  void test_minus_data();

  void test_times();

  void test_times_data();

  void test_compare_to();

  void test_compare_to_data();

  void test_bit_or();

  void test_bit_or_data();

  void test_bit_xor();

  void test_bit_xor_data();

  void test_bit_and();

  void test_bit_and_data();

  void test_modulo();

  void test_modulo_data();

  void test_divided();

  void test_divided_data();

  void test_pow();

  void test_pow_data();

};

#endif // LONGINTTEST_H
