#ifndef INFINITERANDOMTEST_H
#define INFINITERANDOMTEST_H
#include <QtTest/QtTest>
#include "DataStructures/infiniterandom.h"

class InfiniteRandomTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_compare_consistency();
  void test_not_equal();
  void test_equal();
};

#endif // INFINITERANDOMTEST_H
