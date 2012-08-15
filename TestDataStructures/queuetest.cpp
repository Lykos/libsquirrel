#include "queuetest.h"
#include <QtTest/QtTest>
#include <iostream>

#define COMPARE_SIZE(m_queue, expected_size) QCOMPARE((int) (m_queue).size(), (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((int) (actual), (int) (expected))

using namespace DataStructures;

void QueueTest::init()
{
  m_queue = Queue<int>();
  for (int i = 0; i < 20; ++i) {
    m_queue.push(i);
  }
}

void QueueTest::test_default_constructor()
{
  Queue<int> queue1;
  QVERIFY2(queue1.is_empty(), "Default constructed Queue is not empty.");
}

void QueueTest::test_copy_constructor()
{
  Queue<int> copied_m_queue (m_queue);
  QCOMPARE(m_queue, copied_m_queue);
}

void QueueTest::test_push_all()
{
  Queue<int> copied_queue;
  copied_queue.push_all(m_queue.begin() + 5, m_queue.begin() + 14);
  QCOMPARE((int) copied_queue.size(), 9);
  for (int i = 0; i < 9; ++i) {
    QCOMPARE(copied_queue[i], i + 5);
  }
}

void QueueTest::test_assign()
{
  Queue<int> copied_queue;
  copied_queue = m_queue;
  QCOMPARE(m_queue, copied_queue);
}

void QueueTest::test_size()
{
  COMPARE_SIZE(m_queue, 20);
  m_queue.push(20);
  COMPARE_SIZE(m_queue, 21);
  m_queue.push(222);
  COMPARE_SIZE(m_queue, 22);
  m_queue.pop();
  COMPARE_SIZE(m_queue, 21);
  m_queue.pop();
  COMPARE_SIZE(m_queue, 20);
  m_queue.pop();
  COMPARE_SIZE(m_queue, 19);
  m_queue.pop();
  COMPARE_SIZE(m_queue, 18);
  m_queue.push(22);
  COMPARE_SIZE(m_queue, 19);
}

void QueueTest::test_is_empty()
{
  for (int i = 0; i < 20; ++i) {
    QVERIFY(!m_queue.is_empty());
    m_queue.pop();
  }
  QVERIFY(m_queue.is_empty());
  Queue<int> queue2;
  QVERIFY(queue2.is_empty());
  queue2.push(2);
  QVERIFY(!queue2.is_empty());
  queue2.pop();
  QVERIFY(queue2.is_empty());
  Queue<int> queue3;
  queue3.push(2);
  QVERIFY(!queue3.is_empty());
  queue2.push_all(queue3.begin(), queue3.end());
  QVERIFY(!queue2.is_empty());
  queue2.pop();
  QVERIFY(queue2.is_empty());
  queue3.pop();
  QVERIFY(queue3.is_empty());
}

void QueueTest::test_index()
{
  int a = 333;
  try {
    m_queue[-1] = 5;
    QFAIL("m_queue[-1] didn't cause an exception.");
  } catch (Queue<int>::range_error e) {}
  try {
    a = m_queue[-1];
    QFAIL("a = m_queue[-1] didn't cause an exception.");
  } catch (Queue<int>::range_error e) {}
  try {
    m_queue[20] = 5;
    QFAIL("m_queue[-20] didn't cause an exception.");
  } catch (Queue<int>::range_error e) {}
  try {
    a = m_queue[20];
    QFAIL("a = m_queue[20] didn't cause an exception.");
  } catch (Queue<int>::range_error e) {}
  QCOMPARE(a, 333);
}

void QueueTest::test_push() {
  for (int i = 20; i < 25; ++i) {
    m_queue.push(i);
  }
  COMPARE_SIZE(m_queue, 25);
  for (int i = 0; i < 25; ++i) {
    QCOMPARE(m_queue[i], i);
  }
}

void QueueTest::test_pop() {
  for (int n = 0; n < 20; ++n) {
    QCOMPARE(m_queue.pop(), n);
    COMPARE_SIZE(m_queue, 19 - n);
    for (int i = 0; i < 19 - n; ++i) {
      QCOMPARE(m_queue[i], i + n + 1);
    }
  }
  try {
    m_queue.pop();
    QFAIL("Popping from an empty m_queue didn't cause an exception.");
  } catch (Queue<int>::empty_list_error e) {}
}

void QueueTest::test_top() {
  for (int n = 0; n < 20; ++n) {
    QCOMPARE(m_queue.front(), n);
    m_queue.pop();
  }
  int a = 29;
  try {
    a = m_queue.front();
    QFAIL("Popping from an empty m_queue didn't cause an exception.");
  } catch (Queue<int>::empty_list_error e) {}
  QCOMPARE(a, 29);
}

void QueueTest::test_iterate() {
  int i = 0;
  for (Queue<int>::iterator it = m_queue.begin(); it < m_queue.end(); ++it) {
    QCOMPARE(*it, i++);
  }
}

void QueueTest::test_clear() {
  m_queue.clear();
  QVERIFY2(m_queue.is_empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push(22);
  m_queue.clear();
  QVERIFY2(m_queue.is_empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push_all(m_queue.begin(), m_queue.end());
  m_queue.clear();
  QVERIFY2(m_queue.is_empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push(22);
  m_queue.push(0);
  m_queue.clear();
  QVERIFY2(m_queue.is_empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push(22);
}

void QueueTest::test_next_lower()
{
  COMPARE_INTS(next_lower(0), 0);
  for (int k = 0; k < 10; ++k) {
    for (int i = 1 << k; i < 1 << (k + 1); ++i) {
      COMPARE_INTS(next_lower(i), 1 << k);
    }
  }
}

void QueueTest::test_next_higher()
{
  COMPARE_INTS(next_higher(0), 0);
  COMPARE_INTS(next_higher(1), 1);
  for (int k = 0; k < 10; ++k) {
    for (int i = (1 << k) + 1; i <= 1 << (k + 1); ++i) {
      COMPARE_INTS(next_higher(i), 1 << (k + 1));
    }
  }
}

void QueueTest::test_min_capacity()
{
  m_queue.set_min_capacity(55);
  COMPARE_INTS(m_queue.get_min_capacity(), 55);
}

void QueueTest::test_capacity()
{
  m_queue.set_min_capacity(46);
  QVERIFY(m_queue.get_capacity() >= 46);
  for (int i = 0; i < 100; ++i) {
    m_queue.push(0);
    QVERIFY(m_queue.get_capacity() >= 46);
  }
  for (int i = 0; i < 100; ++i) {
    m_queue.pop();
    QVERIFY(m_queue.get_capacity() >= 46);
  }
}


void QueueTest::test_equals()
{
  Queue<int> t1, t2;
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

void QueueTest::test_unequals()
{
  Queue<int> t1, t2;
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