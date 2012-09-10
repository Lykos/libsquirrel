#ifndef LONGINTTEST_H
#define LONGINTTEST_H
#include <QtTest/QtTest>
#include <QElapsedTimer>
#include <string>
#include "DataStructures/longint.h"
#include "performancetest.h"

class LongIntTest : public PerformanceTest
{
  Q_OBJECT
public:
  inline const char* description() const
  {
    return "LongIntTest";
  }

private Q_SLOTS:
  void test_right_shift_data();
  void test_right_shift();
  void test_left_shift_data();
  void test_left_shift();
  void test_inc_data();
  void test_inc();
  void test_dec_data();
  void test_dec();
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
  void test_pow_data();
  void test_pow();
};

#endif // LONGINTTEST_H
