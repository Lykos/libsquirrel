#ifndef TREETEST_HPP
#define TREETEST_HPP

#include "treetest.h"
#include "comparemacros.h"

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_empty_constructor()
{
  Tree< int, DataStructures::Less<int> > t;
  COMPARE_SIZE(t, 0);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::init()
{
  m_tree = Tree< int, DataStructures::Less<int> >();
  standard_fill(m_tree);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::standard_fill(Tree< int, DataStructures::Less<int> >& tree)
{
  for (int i = 0; i < 20; ++i) {
    tree.insert(0);
    tree.insert(i);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_remove()
{
  m_tree.remove(17);
  COMPARE_SIZE(m_tree, 39);
  for (int i = 0; i < 10; ++i) {
    m_tree.remove(0);
    COMPARE_SIZE(m_tree, 38 - i);
  }
  for (int i = 0; i < 10; ++i) {
    m_tree.remove(17);
    COMPARE_SIZE(m_tree, 29);
  }
  for (int i = 0; i < 10; ++i) {
    m_tree.remove(i);
    COMPARE_SIZE(m_tree, 28 - i);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_insert()
{
  Tree< int, DataStructures::Less<int> > t;
  for (int i = 0; i < 5; ++i) {
    t.insert(0);
    COMPARE_SIZE(t, i + 1);
  }
  for (int i = 5; i < 100; ++i) {
    t.insert(rand());
    COMPARE_SIZE(t, i + 1);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_search()
{
  Tree< int, DataStructures::Less<int> > t;
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

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_insert_all()
{
  int a[] = {1, 2, 3, 4, 5, 6, 7};
  Tree< int, DataStructures::Less<int> > t;
  t.insert_all(a + 0, a + 4);
  COMPARE_SIZE(t, 4);
  for (int i = 0; i < 4; ++i) {
    QVERIFY(t.search(a[i]));
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_remove_all()
{
  m_tree.remove_all(0);
  COMPARE_SIZE(m_tree, 19);
  QVERIFY(!m_tree.search(0));
  for (int i = 1; i < 10; ++i) {
    QVERIFY(m_tree.search(i));
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_clear()
{
  Tree< int, DataStructures::Less<int> > t;
  standard_fill(t);
  m_tree.clear();
  COMPARE_SIZE(m_tree, 0);
  standard_fill(m_tree);
  COMPARE_SIZE(m_tree, 40);
  m_tree.clear();
  COMPARE_SIZE(m_tree, 0);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_merge()
{
  Tree< int, DataStructures::Less<int> > t1, t2;
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

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_copy_constructor()
{
  Tree< int, DataStructures::Less<int> > t1;
  standard_fill(t1);
  Tree< int, DataStructures::Less<int> > t2 (t1);
  COMPARE_SIZE(t2, 40);
  for (int i = 0; i < 20; ++i) {
    QVERIFY(t2.search(i));
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_index()
{
  for (int i = 0; i < 20; ++i) {
    COMPARE_INTS(m_tree[i], 0);
    COMPARE_INTS(m_tree[i + 20], i);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_const_index()
{
  const Tree< int, DataStructures::Less<int> >& t = m_tree;
  for (int i = 0; i < 20; ++i) {
    COMPARE_INTS(t[i], 0);
    COMPARE_INTS(t[i + 20], i);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_const_index_errors()
{
  const Tree< int, DataStructures::Less<int> >& t = m_tree;
  int a = 333;
  try {
    a = t[-1];
    QFAIL("a = t[-1] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
  }
  try {
    a = t[50];
    QFAIL("a = t[50] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
  }
  QCOMPARE(a, 333);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_index_errors()
{
  int a = 333;
  try {
    m_tree[-1] = 5;
    QFAIL("m_tree[-1] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
  }
  try {
    a = m_tree[-1];
    QFAIL("a = m_tree[-1] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
 }
  try {
    m_tree[50] = 5;
    QFAIL("m_tree[50] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
  }
  try {
    a = m_tree[50];
    QFAIL("a = m_tree[50] didn't cause an exception.");
  } catch (DataStructures::PreconditionViolation e) {
    QCOMPARE(e.type(), DataStructures::OutOfRange);
  }
  QCOMPARE(a, 333);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_iterators()
{
  int i = 0;
  for (typename Tree< int, DataStructures::Less<int> >::iterator it = m_tree.begin(); it < m_tree.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, m_tree[i]);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_const_iterators()
{
  const Tree< int, DataStructures::Less<int> >& t = m_tree;
  int i = 0;
  for (typename Tree< int, DataStructures::Less<int> >::const_iterator it = m_tree.begin(); it < m_tree.end(); ++it, ++i)
  {
    COMPARE_INTS(*it, t[i]);
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_upper_bound_const()
{
  const Tree< int, DataStructures::Less<int> >& t = m_tree;
  QCOMPARE(t.upper_bound(0), t.begin() + 21);
  QCOMPARE(t.upper_bound(-1), t.begin());
  QCOMPARE(t.upper_bound(1), t.begin() + 22);
  QCOMPARE(t.upper_bound(100), t.end());
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_upper_bound()
{
  Tree< int, DataStructures::Less<int> > t;
  standard_fill(t);
  QCOMPARE(t.upper_bound(0), t.begin() + 21);
  QCOMPARE(t.upper_bound(-1), t.begin());
  QCOMPARE(t.upper_bound(1), t.begin() + 22);
  QCOMPARE(t.upper_bound(100), t.end());
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_lower_bound_const()
{
  const Tree< int, DataStructures::Less<int> >& t = m_tree;
  QCOMPARE(t.lower_bound(0), t.begin());
  QCOMPARE(t.lower_bound(-1), t.begin());
  QCOMPARE(t.lower_bound(1), t.begin() + 21);
  QCOMPARE(t.lower_bound(100), t.end());
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_lower_bound()
{
  QCOMPARE(m_tree.lower_bound(0), m_tree.begin());
  QCOMPARE(m_tree.lower_bound(-1), m_tree.begin());
  QCOMPARE(m_tree.lower_bound(1), m_tree.begin() + 21);
  QCOMPARE(m_tree.lower_bound(100), m_tree.end());
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_assign()
{
  Tree< int, DataStructures::Less<int> > t;
  t.insert(-1);
  t = m_tree;
  COMPARE_SIZE(t, 40);
  QVERIFY(!t.search(-1));
  for (int i = 0; i < 20; ++i) {
    QVERIFY(t.search(i));
  }
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_equals()
{
  Tree< int, DataStructures::Less<int> > t1, t2;
  QVERIFY(t1 == t2);
  standard_fill(t1);
  QVERIFY(!(t1 == t2));
  QVERIFY(t1 == t1);
  for (int i = 0; i < 20; ++i) {
    t2.insert(i);
  }
  QVERIFY(!(t1 == t2));
  for (int i = 0; i < 20; ++i) {
    t2.insert(0);
  }
  QVERIFY(t1 == t2);
}

template <template <typename T, typename Compare> class Tree>
void TreeTest<Tree>::test_not_equals()
{
  Tree< int, DataStructures::Less<int> > t1, t2;
  QVERIFY(!(t1 != t2));
  standard_fill(t1);
  QVERIFY(t1 != t2);
  QVERIFY(!(t1 != t1));
  for (int i = 0; i < 20; ++i) {
    t2.insert(i);
  }
  QVERIFY(t1 != t2);
  for (int i = 0; i < 20; ++i) {
    t2.insert(0);
  }
  QVERIFY(!(t1 != t2));
}

#endif // TREETEST_HPP
