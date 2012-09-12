#ifndef FINITEELEMENTTEST_H
#define FINITEELEMENTTEST_H

#include <QtTest/QtTest>

class FiniteElementTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_pow_data();

  void test_pow();

  void test_divide_data();

  void test_divide();
};

#endif // FINITEELEMENTTEST_H
