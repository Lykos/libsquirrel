#include <iostream>
#include "arraylisttest.h"
#define COMPARE_SIZE(list, expected_size) QCOMPARE((int) (list).size(), (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((int) (actual), (int) (expected))

using namespace DataStructures;

ArrayListTest::ArrayListTest():
  list(20)
{
}

void ArrayListTest::init()
{
  list = ArrayList<int>(20);
  for (int i = 1; i < 20; ++i) {
    list[i] = i;
  }
}

void ArrayListTest::test_default_constructor()
{
  ArrayList<int> list1;
  QVERIFY2(list1.is_empty(), "Default constructed list is not empty.");
  ArrayList<int> list5 (5);
  QVERIFY2(!list5.is_empty(), "List with 5 elements is empty.");
  COMPARE_SIZE(list5, 5);
}

void ArrayListTest::test_fill_constructor()
{
  ArrayList<int> list1 (6);
  for (int i = 0; i < 6; ++i) {
    QCOMPARE(list1[i], 0);
  }
  ArrayList<int> list2 (6, 122);
  for (int i = 0; i < 6; ++i) {
    QCOMPARE(list2[i], 122);
  }
}

void ArrayListTest::test_copy_constructor()
{
  ArrayList<int> copied_list (list);
  QCOMPARE(list, copied_list);
}

void ArrayListTest::test_push_all()
{
  ArrayList<int> copied_list;
  copied_list.push_all(list.begin() + 5, list.begin() + 14);
  QCOMPARE((int) copied_list.size(), 9);
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_list[i], i + 5);
  }
}

void ArrayListTest::test_assign()
{
  ArrayList<int> copied_list;
  copied_list = list;
  QCOMPARE(list, copied_list);
}

void ArrayListTest::test_plus()
{
  ArrayList<int> prefix (5, 677);
  ArrayList<int> postfix(10, 174);
  ArrayList<int> together (prefix + list + postfix);
  COMPARE_SIZE(together, 35);
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(together[i], 677);
  }
  for (int i = 5; i < 25; ++i) {
    QCOMPARE(together[i], i - 5);
  }
  for (int i = 25; i < 35; ++i) {
    QCOMPARE(together[i], 174);
  }
}

void ArrayListTest::test_plus_assign()
{
  ArrayList<int> postfix(11, 1);
  list += postfix;
  COMPARE_SIZE(list, 31);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 20; i < 31; ++i) {
    QCOMPARE(list[i], 1);
  }
}

void ArrayListTest::test_times()
{
  ArrayList<int> lists5 (list * 5);
  COMPARE_SIZE(lists5, 100);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 20; ++j) {
      QCOMPARE(lists5[i * 20 + j], j);
    }
  }
}

void ArrayListTest::test_times_assign() {
  list *= 3;
  QCOMPARE((int) list.size(), 60);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 20; ++j) {
      QCOMPARE(list[i * 20 + j], j);
    }
  }
}

void ArrayListTest::test_size()
{
  COMPARE_SIZE(list, 20);
  list += list;
  COMPARE_SIZE(list, 40);
  list.push(20);
  COMPARE_SIZE(list, 41);
  list.push(222);
  COMPARE_SIZE(list, 42);
  list.pop();
  COMPARE_SIZE(list, 41);
  list.pop();
  COMPARE_SIZE(list, 40);
  list.pop();
  COMPARE_SIZE(list, 39);
  list.pop();
  COMPARE_SIZE(list, 38);
  list.push(22);
  COMPARE_SIZE(list, 39);
}

void ArrayListTest::test_is_empty()
{
  for (int i = 0; i < 20; ++i) {
    QVERIFY(!list.is_empty());
    list.pop();
  }
  QVERIFY(list.is_empty());
  ArrayList<int> list2;
  QVERIFY(list2.is_empty());
  list2.push(2);
  QVERIFY(!list2.is_empty());
  list2.pop();
  QVERIFY(list2.is_empty());
  ArrayList<int> list3 (1);
  QVERIFY(!list3.is_empty());
  list2 += list3;
  QVERIFY(!list2.is_empty());
  list2.pop();
  QVERIFY(list2.is_empty());
  list3.pop();
  QVERIFY(list3.is_empty());
}

void ArrayListTest::test_const_index_errors()
{
  const ArrayList<int>& l = list;
  int a = 333;
  try {
    a = l[-1];
    QFAIL("a = l[-1] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  try {
    a = l[20];
    QFAIL("a = l[20] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  QCOMPARE(a, 333);
}

void ArrayListTest::test_index_errors()
{
  int a = 333;
  try {
    list[-1] = 5;
    QFAIL("list[-1] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  try {
    a = list[-1];
    QFAIL("a = list[-1] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  try {
    list[20] = 5;
    QFAIL("list[-20] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  try {
    a = list[20];
    QFAIL("a = list[20] didn't cause an exception.");
  } catch (ArrayList<int>::range_error e) {}
  QCOMPARE(a, 333);
}

void ArrayListTest::test_push() {
  for (int i = 20; i < 25; ++i) {
    list.push(i);
  }
  COMPARE_SIZE(list, 25);
  for (int i = 0; i < 25; ++i) {
    QCOMPARE(list[i], i);
  }
}

void ArrayListTest::test_pop() {
  for (int n = 19; n >= 0; --n) {
    QCOMPARE(list.pop(), n);
    COMPARE_SIZE(list, n);
    for (int i = 0; i < n; ++i) {
      QCOMPARE(list[i], i);
    }
  }
  try {
    list.pop();
    QFAIL("Popping from an empty list didn't cause an exception.");
  } catch (ArrayList<int>::empty_list_error e) {}
}

void ArrayListTest::test_top() {
  for (int n = 19; n >= 0; --n) {
    QCOMPARE(list.back(), n);
    list.pop();
  }
  int a = 29;
  try {
    a = list.back();
    QFAIL("Popping from an empty list didn't cause an exception.");
  } catch (ArrayList<int>::empty_list_error e) {}
  QCOMPARE(a, 29);
}

void ArrayListTest::test_iterate() {
  int i = 0;
  for (ArrayList<int>::iterator it = list.begin(); it < list.end(); ++it) {
    QCOMPARE(*it, i++);
  }
}

void ArrayListTest::test_clear() {
  list.clear();
  QVERIFY2(list.is_empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push(22);
  list.clear();
  QVERIFY2(list.is_empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list += list;
  list.clear();
  QVERIFY2(list.is_empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push(22);
  list += ArrayList<int>(2);
  list.clear();
  QVERIFY2(list.is_empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push(22);
}

void ArrayListTest::test_next_lower()
{
  COMPARE_INTS(next_lower(0), 0);
  for (int k = 0; k < 10; ++k) {
    for (int i = 1 << k; i < 1 << (k + 1); ++i) {
      COMPARE_INTS(next_lower(i), 1 << k);
    }
  }
}

void ArrayListTest::test_next_higher()
{
  COMPARE_INTS(next_higher(0), 0);
  COMPARE_INTS(next_higher(1), 1);
  for (int k = 0; k < 10; ++k) {
    for (int i = (1 << k) + 1; i <= 1 << (k + 1); ++i) {
      COMPARE_INTS(next_higher(i), 1 << (k + 1));
    }
  }
}

void ArrayListTest::test_min_capacity()
{
  list.set_min_capacity(55);
  COMPARE_INTS(list.min_capacity(), 55);
}

void ArrayListTest::test_capacity()
{
  list.set_min_capacity(46);
  QVERIFY(list.capacity() >= 46);
  for (int i = 0; i < 100; ++i) {
    list.push(0);
    QVERIFY(list.capacity() >= 46);
  }
  for (int i = 0; i < 100; ++i) {
    list.pop();
    QVERIFY(list.capacity() >= 46);
  }
}


void ArrayListTest::test_equals()
{
  ArrayList<int> t1, t2;
  QVERIFY(t1 == t2);
  for (index_type i = 0; i < 30; ++i) {
    t1.push(i);
  }
  QVERIFY(t1 == t1);
  QVERIFY(!(t1 == t2));
  for (index_type i = 0; i < 30; ++i) {
    t2.push(i);
  }
  QVERIFY(t2 == t2);
}

void ArrayListTest::test_unequals()
{
  ArrayList<int> t1, t2;
  QVERIFY(!(t1 != t2));
  for (index_type i = 0; i < 30; ++i) {
    t1.push(i);
  }
  QVERIFY(!(t1 != t1));
  QVERIFY(t1 != t2);
  for (index_type i = 0; i < 30; ++i) {
    t2.push(i);
  }
  QVERIFY(!(t1 != t2));
}
