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

void TreapTest::init()
{
  m_treap = Treap<int>();
  standard_fill(m_treap);
}

void TreapTest::standard_fill(Treap<int>& treap)
{
  for (index_type i = 0; i < 20; ++i) {
    treap.insert(0);
    treap.insert(i);
  }
}

void TreapTest::test_remove()
{
  m_treap.remove(17);
  COMPARE_SIZE(m_treap, 39);
  for (index_type i = 0; i < 10; ++i) {
    m_treap.remove(0);
    COMPARE_SIZE(m_treap, 38 - i);
  }
  for (index_type i = 0; i < 10; ++i) {
    m_treap.remove(17);
    COMPARE_SIZE(m_treap, 29);
  }
  for (index_type i = 0; i < 10; ++i) {
    m_treap.remove(i);
    COMPARE_SIZE(m_treap, 28 - i);
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
  m_treap.remove_all(0);
  COMPARE_SIZE(m_treap, 19);
  QVERIFY(!m_treap.search(0));
  for (index_type i = 1; i < 10; ++i) {
    QVERIFY(m_treap.search(i));
  }
}

void TreapTest::test_clear()
{
  Treap<int> t;
  standard_fill(t);
  m_treap.clear();
  COMPARE_SIZE(m_treap, 0);
  standard_fill(m_treap);
  COMPARE_SIZE(m_treap, 40);
  m_treap.clear();
  COMPARE_SIZE(m_treap, 0);
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
  for (index_type i = 0; i < 20; ++i) {
    COMPARE_INTS(m_treap[i], 0);
    COMPARE_INTS(m_treap[i + 20], i);
  }
}

void TreapTest::test_const_index()
{
  const Treap<int>& t = m_treap;
  for (index_type i = 0; i < 20; ++i) {
    COMPARE_INTS(t[i], 0);
    COMPARE_INTS(t[i + 20], i);
  }
}

void TreapTest::test_const_index_errors()
{
  const Treap<int>& t = m_treap;
  int a = 333;
  try {
    a = t[-1];
    QFAIL("a = t[-1] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  try {
    a = t[50];
    QFAIL("a = t[50] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  QCOMPARE(a, 333);
}

void TreapTest::test_index_errors()
{
  int a = 333;
  try {
    m_treap[-1] = 5;
    QFAIL("m_treap[-1] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  try {
    a = m_treap[-1];
    QFAIL("a = m_treap[-1] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  try {
    m_treap[50] = 5;
    QFAIL("m_treap[50] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  try {
    a = m_treap[50];
    QFAIL("a = m_treap[50] didn't cause an exception.");
  } catch (Treap<int>::range_error e) {}
  QCOMPARE(a, 333);
}

void TreapTest::test_iterators()
{
  index_type i = 0;
  for (Treap<int>::iterator it = m_treap.begin(); it < m_treap.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, m_treap[i]);
  }
}

void TreapTest::test_const_iterators()
{
  const Treap<int>& t = m_treap;
  index_type i = 0;
  for (Treap<int>::const_iterator it = m_treap.begin(); it < m_treap.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, t[i]);
  }
}

void TreapTest::test_upper_bound_const()
{
  const Treap<int>& t = m_treap;
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
  const Treap<int>& t = m_treap;
  QCOMPARE(t.lower_bound(0), t.begin());
  QCOMPARE(t.lower_bound(-1), t.begin());
  QCOMPARE(t.lower_bound(1), t.begin() + 21);
  QCOMPARE(t.lower_bound(100), t.end());
}

void TreapTest::test_lower_bound()
{
  QCOMPARE(m_treap.lower_bound(0), m_treap.begin());
  QCOMPARE(m_treap.lower_bound(-1), m_treap.begin());
  QCOMPARE(m_treap.lower_bound(1), m_treap.begin() + 21);
  QCOMPARE(m_treap.lower_bound(100), m_treap.end());
}

void TreapTest::test_assign()
{
  Treap<int> t;
  t.insert(-1);
  t = m_treap;
  COMPARE_SIZE(t, 40);
  QVERIFY(!t.search(-1));
  for (int i = 0; i < 20; ++i) {
    QVERIFY(t.search(i));
  }
}

void TreapTest::test_equals()
{
  Treap<int> t1, t2;
  QVERIFY(t1 == t2);
  standard_fill(t1);
  QVERIFY(!(t1 == t2));
  QVERIFY(t1 == t1);
  for (index_type i = 0; i < 20; ++i) {
    t2.insert(i);
  }
  QVERIFY(!(t1 == t2));
  for (index_type i = 0; i < 20; ++i) {
    t2.insert(0);
  }
  QVERIFY(t1 == t2);
}

void TreapTest::test_not_equals()
{
  Treap<int> t1, t2;
  QVERIFY(!(t1 != t2));
  standard_fill(t1);
  QVERIFY(t1 != t2);
  QVERIFY(!(t1 != t1));
  for (index_type i = 0; i < 20; ++i) {
    t2.insert(i);
  }
  QVERIFY(t1 != t2);
  for (index_type i = 0; i < 20; ++i) {
    t2.insert(0);
  }
  QVERIFY(!(t1 != t2));
}
