#ifndef LONGINTTEST_H
#define LONGINTTEST_H
#include <QtTest/QtTest>
#include "longint.h"

class LongIntTest : public QObject
{
  Q_OBJECT

public:
  LongIntTest();

private:
  DataStructures::LongInt number;

private Q_SLOTS:
  void init();
  void test_upper_half();
  void test_lower_half();
  void test_empty_constructor();
  void test_default_constructor_data();
  void test_default_constructor();
  void test_copy_constructor_data();
  void test_copy_constructor();
  void test_assign_data();
  void test_assign();
  void test_string_constructor_data();
  void test_string_constructor();
  void test_compare_to_data();
  void test_compare_to();
  void test_inc_data();
  void test_inc();
  void test_dec_data();
  void test_dec();
  void test_unary_minus_data();
  void test_unary_minus();
  void test_unary_plus_data();
  void test_unary_plus();
  void test_bit_negate_data();
  void test_bit_negate();
  void test_plus_data();
  void test_plus();
  void test_minus_data();
  void test_minus();
  void test_times_data();
  void test_times();
  void test_modulo_data();
  void test_modulo();
  void test_divided_data();
  void test_divided();
  void test_left_shift_data();
  void test_left_shift();
  void test_right_shift_data();
  void test_right_shift();
  void test_bit_or_data();
  void test_bit_or();
  void test_bit_xor_data();
  void test_bit_xor();
  void test_bit_and_data();
  void test_bit_and();
  void test_pow_data();
  void test_pow();
};

#endif // LONGINTTEST_H
