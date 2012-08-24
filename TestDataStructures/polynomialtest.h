#ifndef POLYNOMIALTEST_H
#define POLYNOMIALTEST_H

#include <QtTest/QtTest>

class PolynomialTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_pow_data();

  void test_pow();

  void test_evaluate_data();

  void test_evaluate();

  void test_modulo_data();

  void test_modulo();

  void test_divide_data();

  void test_divide();
};

#endif // POLYNOMIALTEST_H
