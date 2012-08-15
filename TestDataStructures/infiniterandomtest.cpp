#include "infiniterandomtest.h"

using namespace DataStructures;

void InfiniteRandomTest::test_compare_consistency()
{
  for (unsigned int i = 0; i < 100; ++i) {
    InfiniteRandom a, b;
    bool smaller = a < b;
    QCOMPARE(a < b, smaller);
    QCOMPARE(a <= b, smaller);
    QCOMPARE(a > b, !smaller);
    QCOMPARE(a >= b, !smaller);
  }
}

void InfiniteRandomTest::test_equal()
{
  for (unsigned int i = 0; i < 100; ++i) {
    InfiniteRandom a;
    QVERIFY(a == a);
    QVERIFY(!(a != a));
  }
}

void InfiniteRandomTest::test_not_equal()
{
  for (unsigned int i = 0; i < 100; ++i) {
    InfiniteRandom a, b;
    QVERIFY(a != b);
    QVERIFY(!(a == b));
  }
}
