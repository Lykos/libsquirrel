#include "arraylisttest.h"
#include "comparemacros.h"
#include "DataStructures/preconditionviolation.h"
#include <iostream>

using namespace DataStructures;
using namespace std;

ArrayListTest::ArrayListTest():
  list(20)
{}

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
  QVERIFY2(list1.empty(), "Default constructed list is not empty.");
  ArrayList<int> list5 (5);
  QVERIFY2(!list5.empty(), "List with 5 elements is empty.");
  COMPARE_SIZE(list5, 5);
}

void ArrayListTest::test_fill_constructor()
{
  ArrayList<int> list1 (6);
  for (int i = 0; i < 6; ++i) {
    QCOMPARE(list1[i], 0);
  }
  ArrayList<int> list2 (6ull, 122);
  for (int i = 0; i < 6; ++i) {
    QCOMPARE(list2[i], 122);
  }
}

void ArrayListTest::test_copy_constructor()
{
  ArrayList<int> copied_list (list);
  QCOMPARE(list, copied_list);
}

void ArrayListTest::test_erase_index_range()
{
  list.erase(4, 10);
  COMPARE_SIZE(list, 14);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 10; i < 20; ++i) {
    QCOMPARE(list[i - 6], i);
  }
}

void ArrayListTest::test_erase_index_element()
{
  list.erase(4);
  COMPARE_SIZE(list, 19);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 5; i < 20; ++i) {
    QCOMPARE(list[i - 1], i);
  }
}

void ArrayListTest::test_erase_iterator_range()
{
  list.erase(list.begin() + 4, list.begin() + 10);
  COMPARE_SIZE(list, 14);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 10; i < 20; ++i) {
    QCOMPARE(list[i - 6], i);
  }
}

void ArrayListTest::test_erase_iterator_element()
{
  list.erase(list.begin() + 4);
  COMPARE_SIZE(list, 19);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 5; i < 20; ++i) {
    QCOMPARE(list[i - 1], i);
  }
}

void ArrayListTest::test_insert_index_range()
{
  ArrayList<int> copied_list;
  copied_list.insert(copied_list.size(), list.begin() + 5, list.begin() + 14);
  COMPARE_SIZE(copied_list, 9);
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_list[i], i + 5);
  }
  copied_list.insert(4, list.begin() + 5, list.begin() + 14);
  COMPARE_SIZE(copied_list, 18);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(copied_list[i], i + 5);
  }
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_list[i + 4], i + 5);
  }
  for (int i = 4; i < 9; ++i) {
    QCOMPARE(copied_list[i + 9], i + 5);
  }
}

void ArrayListTest::test_insert_index_element()
{
  list.insert(list.size(), 1);
  COMPARE_SIZE(list, 21);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i], i);
  }
  QCOMPARE(list[20], 1);
  list.insert(0, 5);
  COMPARE_SIZE(list, 22);
  QCOMPARE(list[0], 5);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 1], i);
  }
  QCOMPARE(list[21], 1);
  list.insert(1, 17);
  COMPARE_SIZE(list, 23);
  QCOMPARE(list[0], 5);
  QCOMPARE(list[1], 17);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 2], i);
  }
  QCOMPARE(list[22], 1);
}

void ArrayListTest::test_insert_index_fill()
{
  list.insert(list.size(), 5ul, 1);
  COMPARE_SIZE(list, 25);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 20], 1);
  }
  list.insert(0, 4ul, 5);
  COMPARE_SIZE(list, 29);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], 5);
  }
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 4], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 24], 1);
  }
  list.insert(4, 17ul, 1716);
  COMPARE_SIZE(list, 46);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], 5);
  }
  for (int i = 0; i < 17; ++i) {
    QCOMPARE(list[i + 4], 1716);
  }
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 21], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 41], 1);
  }
}

void ArrayListTest::test_insert_iterator_range()
{
  ArrayList<int> copied_list;
  copied_list.insert(copied_list.end(), list.begin() + 5, list.begin() + 14);
  COMPARE_SIZE(copied_list, 9);
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_list[i], i + 5);
  }
  copied_list.insert(copied_list.begin() + 4, list.begin() + 5, list.begin() + 14);
  COMPARE_SIZE(copied_list, 18);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(copied_list[i], i + 5);
  }
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_list[i + 4], i + 5);
  }
  for (int i = 4; i < 9; ++i) {
    QCOMPARE(copied_list[i + 9], i + 5);
  }
}

void ArrayListTest::test_insert_iterator_element()
{
  list.insert(list.end(), 1);
  COMPARE_SIZE(list, 21);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i], i);
  }
  QCOMPARE(list[20], 1);
  list.insert(list.begin(), 5);
  COMPARE_SIZE(list, 22);
  QCOMPARE(list[0], 5);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 1], i);
  }
  QCOMPARE(list[21], 1);
  list.insert(list.begin() + 1, 17);
  COMPARE_SIZE(list, 23);
  QCOMPARE(list[0], 5);
  QCOMPARE(list[1], 17);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 2], i);
  }
  QCOMPARE(list[22], 1);
}

void ArrayListTest::test_insert_iterator_fill()
{
  list.insert(list.end(), 5ul, 1);
  COMPARE_SIZE(list, 25);
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 20], 1);
  }
  list.insert(list.begin(), 4ul, 5);
  COMPARE_SIZE(list, 29);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], 5);
  }
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 4], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 24], 1);
  }
  list.insert(list.begin() + 4, 17ul, 1716);
  COMPARE_SIZE(list, 46);
  for (int i = 0; i < 4; ++i) {
    QCOMPARE(list[i], 5);
  }
  for (int i = 0; i < 17; ++i) {
    QCOMPARE(list[i + 4], 1716);
  }
  for (int i = 0; i < 20; ++i) {
    QCOMPARE(list[i + 21], i);
  }
  for (int i = 0; i < 5; ++i) {
    QCOMPARE(list[i + 41], 1);
  }
}

void ArrayListTest::test_assign()
{
  ArrayList<int> copied_list;
  copied_list = list;
  QCOMPARE(list, copied_list);
}

void ArrayListTest::test_size()
{
  COMPARE_SIZE(list, 20);
  list.insert(list.end(), list.begin(), list.end());
  COMPARE_SIZE(list, 40);
  list.push_back(20);
  COMPARE_SIZE(list, 41);
  list.push_back(222);
  COMPARE_SIZE(list, 42);
  list.pop_back();
  COMPARE_SIZE(list, 41);
  list.pop_back();
  COMPARE_SIZE(list, 40);
  list.pop_back();
  COMPARE_SIZE(list, 39);
  list.pop_back();
  COMPARE_SIZE(list, 38);
  list.push_back(22);
  COMPARE_SIZE(list, 39);
}

void ArrayListTest::test_is_empty()
{
  for (int i = 0; i < 20; ++i) {
    QVERIFY(!list.empty());
    list.pop_back();
  }
  QVERIFY(list.empty());
  ArrayList<int> list2;
  QVERIFY(list2.empty());
  list2.push_back(2);
  QVERIFY(!list2.empty());
  list2.pop_back();
  QVERIFY(list2.empty());
  ArrayList<int> list3 (1);
  QVERIFY(!list3.empty());
  list2.insert(list2.begin(), list3.begin(), list3.end());
  QVERIFY(!list2.empty());
  list2.pop_back();
  QVERIFY(list2.empty());
  list3.pop_back();
  QVERIFY(list3.empty());
}

void ArrayListTest::test_const_index_errors()
{
  const ArrayList<int>& l = list;
  int a = 333;
  try {
    a = l[-1];
    QFAIL("a = l[-1] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  try {
    a = l[20];
    QFAIL("a = l[20] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  QCOMPARE(a, 333);
}

void ArrayListTest::test_index_errors()
{
  int a = 333;
  try {
    list[-1] = 5;
    QFAIL("list[-1] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  try {
    a = list[-1];
    QFAIL("a = list[-1] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  try {
    list[20] = 5;
    QFAIL("list[-20] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  try {
    a = list[20];
    QFAIL("a = list[20] didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  QCOMPARE(a, 333);
}

void ArrayListTest::test_push() {
  for (int i = 20; i < 25; ++i) {
    list.push_back(i);
  }
  COMPARE_SIZE(list, 25);
  for (int i = 0; i < 25; ++i) {
    QCOMPARE(list[i], i);
  }
}

void ArrayListTest::test_pop() {
  for (int n = 19; n >= 0; --n) {
    QCOMPARE(list.pop_back(), n);
    COMPARE_SIZE(list, n);
    for (int i = 0; i < n; ++i) {
      QCOMPARE(list[i], i);
    }
  }
  try {
    list.pop_back();
    QFAIL("Popping from an empty list didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), EmptyList);
  }
}

void ArrayListTest::test_top() {
  for (int n = 19; n >= 0; --n) {
    QCOMPARE(list.back(), n);
    list.pop_back();
  }
  int a = 29;
  try {
    a = list.back();
    QFAIL("Popping from an empty list didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), EmptyList);
  }
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
  QVERIFY2(list.empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push_back(22);
  list.clear();
  QVERIFY2(list.empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.insert(list.end(), list.begin(), list.end());
  list.clear();
  QVERIFY2(list.empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push_back(22);
  list.insert(list.end(), 2ul, 34);
  list.clear();
  QVERIFY2(list.empty(), "Emptied list is not empty.");
  COMPARE_SIZE(list, 0);
  list.push_back(22);
}

void ArrayListTest::test_min_capacity()
{
  list.min_capacity(55);
  COMPARE_INTS(list.min_capacity(), 55);
}

void ArrayListTest::test_capacity()
{
  list.min_capacity(46);
  QVERIFY(list.capacity() >= 46);
  for (int i = 0; i < 100; ++i) {
    list.push_back(0);
    QVERIFY(list.capacity() >= 46);
  }
  for (int i = 0; i < 100; ++i) {
    list.pop_back();
    QVERIFY(list.capacity() >= 46);
  }
}


void ArrayListTest::test_equals()
{
  ArrayList<int> t1, t2;
  QVERIFY(t1 == t2);
  for (int i = 0; i < 30; ++i) {
    t1.push_back(i);
  }
  QVERIFY(t1 == t1);
  QVERIFY(!(t1 == t2));
  for (int i = 0; i < 30; ++i) {
    t2.push_back(i);
  }
  QVERIFY(t2 == t2);
}

void ArrayListTest::test_unequals()
{
  ArrayList<int> t1, t2;
  QVERIFY(!(t1 != t2));
  for (int i = 0; i < 30; ++i) {
    t1.push_back(i);
  }
  QVERIFY(!(t1 != t1));
  QVERIFY(t1 != t2);
  for (int i = 0; i < 30; ++i) {
    t2.push_back(i);
  }
  QVERIFY(!(t1 != t2));
}
