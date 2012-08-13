#include <QtTest/QtTest>
#include <iostream>
#include "treaptest.h"

#define COMPARE_SIZE(treap, expected_size) QCOMPARE((int) (treap).size(), (int) (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((int) (actual), (int) (expected))

using namespace DataStructures;

void TreapTest::test_empty_constructor()
{
  Treap<int> t;
  COMPARE_SIZE(t, 0);
}

void TreapTest::standard_fill(Treap<int>& t)
{
  for (index_type i = 0; i < 20; ++i) {
    t.insert(0);
    t.insert(i);
  }
}

void TreapTest::test_remove()
{
  Treap<int> t;
  standard_fill(t);
  t.remove(17);
  COMPARE_SIZE(t, 39);
  for (index_type i = 0; i < 10; ++i) {
    t.remove(0);
    COMPARE_SIZE(t, 38 - i);
  }
  for (index_type i = 0; i < 10; ++i) {
    t.remove(17);
    COMPARE_SIZE(t, 29);
  }
  for (index_type i = 0; i < 10; ++i) {
    t.remove(i);
    COMPARE_SIZE(t, 28 - i);
  }
}

void TreapTest::test_insert()
{
  Treap<int> t;
  for (index_type i = 0; i < 5; ++i) {
    t.insert(0);
    COMPARE_SIZE(t, i + 1);
  }
  for (index_type i = 5; i < 100; ++i) {
    t.insert(rand());
    COMPARE_SIZE(t, i + 1);
  }
}

void TreapTest::test_search()
{
  Treap<int> t;
  QVERIFY(!t.search(-1));
  t.insert(1);
  QVERIFY(!t.search(-1));
  QVERIFY(t.search(1));
  t.insert(1);
  QVERIFY(!t.search(-1));
  QVERIFY(t.search(1));
  t.insert(2);
  QVERIFY(!t.search(-1));
  QVERIFY(t.search(1));
  QVERIFY(t.search(2));
  t.insert(-1);
  QVERIFY(t.search(-1));
  QVERIFY(t.search(1));
  QVERIFY(t.search(2));
}

void TreapTest::test_insert_all()
{
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  Treap<int> t;
  t.insert_all(a + 0, a + 4);
  COMPARE_SIZE(t, 4);
  for (index_type i = 0; i < 4; ++i) {
    QVERIFY(t.search(a[i]));
  }
}

void TreapTest::test_remove_all()
{
  Treap<int> t;
  for (index_type i = 0; i < 10; ++i) {
    t.insert(0);
    t.insert(i);
  }
  t.remove_all(0);
  COMPARE_SIZE(t, 9);
  QVERIFY(!t.search(0));
  for (index_type i = 1; i < 10; ++i) {
    QVERIFY(t.search(i));
  }
}

void TreapTest::test_clear()
{
  Treap<int> t;
  standard_fill(t);
  t.clear();
  COMPARE_SIZE(t, 0);
  standard_fill(t);
  COMPARE_SIZE(t, 40);
  t.clear();
  COMPARE_SIZE(t, 0);
}

void TreapTest::test_merge()
{
  Treap<int> t1, t2;
  standard_fill(t2);
  t1.insert(-2);
  t1.insert(-1);
  t1.merge(t2);
  COMPARE_SIZE(t1, 42);
  COMPARE_SIZE(t2, 40);
  for (int i = -2; i < 20; ++i) {
    QVERIFY(t1.search(i));
  }
}

void TreapTest::test_copy_constructor()
{
  Treap<int> t1;
  standard_fill(t1);
  Treap<int> t2 (t1);
  COMPARE_SIZE(t2, 40);
  for (int i = 0; i < 20; ++i) {
    QVERIFY(t2.search(i));
  }
}

void TreapTest::test_index()
{
  Treap<int> t;
  standard_fill(t);
  for (index_type i = 0; i < 20; ++i) {
    COMPARE_INTS(t[i], 0);
    COMPARE_INTS(t[i + 20], i);
  }
}

void TreapTest::test_const_index()
{
  Treap<int> t2;
  standard_fill(t2);
  const Treap<int>& t = t2;
  for (index_type i = 0; i < 20; ++i) {
    COMPARE_INTS(t[i], 0);
    COMPARE_INTS(t[i + 20], i);
  }
}

void TreapTest::test_iterators()
{
  Treap<int> t;
  standard_fill(t);
  index_type i = 0;
  for (Treap<int>::iterator it = t.begin(); it < t.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, t[i]);
  }
}

void TreapTest::test_const_iterators()
{
  Treap<int> t2;
  standard_fill(t2);
  const Treap<int>& t = t2;
  index_type i = 0;
  for (Treap<int>::const_iterator it = t.begin(); it < t.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, t[i]);
  }
}

void TreapTest::test_upper_bound_const()
{
  Treap<int> t2;
  standard_fill(t2);
  const Treap<int>& t = t2;
  QCOMPARE(t.upper_bound(0), t.begin() + 21);
  QCOMPARE(t.upper_bound(-1), t.begin());
  QCOMPARE(t.upper_bound(1), t.begin() + 22);
  QCOMPARE(t.upper_bound(100), t.end());
}

void TreapTest::test_upper_bound()
{
  Treap<int> t;
  standard_fill(t);
  QCOMPARE(t.upper_bound(0), t.begin() + 21);
  QCOMPARE(t.upper_bound(-1), t.begin());
  QCOMPARE(t.upper_bound(1), t.begin() + 22);
  QCOMPARE(t.upper_bound(100), t.end());
}

void TreapTest::test_lower_bound_const()
{
  Treap<int> t2;
  standard_fill(t2);
  const Treap<int>& t = t2;
  QCOMPARE(t.lower_bound(0), t.begin());
  QCOMPARE(t.lower_bound(-1), t.begin());
  QCOMPARE(t.lower_bound(1), t.begin() + 21);
  QCOMPARE(t.lower_bound(100), t.end());
}

void TreapTest::test_lower_bound()
{
  Treap<int> t;
  standard_fill(t);
  QCOMPARE(t.lower_bound(0), t.begin());
  QCOMPARE(t.lower_bound(-1), t.begin());
  QCOMPARE(t.lower_bound(1), t.begin() + 21);
  QCOMPARE(t.lower_bound(100), t.end());
}

void TreapTest::test_assign()
{
  Treap<int> t, t2;
  standard_fill(t2);
  t.insert(-1);
  t = t2;
  COMPARE_SIZE(t, 40);
  QVERIFY(!t.search(-1));
  for (int i = 0; i < 20; ++i) {
    QVERIFY(t2.search(i));
  }
}

void TreapTest::test_equals()
{
  Treap<int> t1, t2;
  QVERIFY(t1 == t2);
  standard_fill(t1);
  QVERIFY(!(t1 == t2));
  standard_fill(t2);
  QVERIFY(t1 == t2);
}

void TreapTest::test_not_equals()
{
  Treap<int> t1, t2;
  QVERIFY(!(t1 != t2));
  standard_fill(t1);
  QVERIFY(t1 != t2);
  standard_fill(t2);
  QVERIFY(!(t1 != t2));
}
