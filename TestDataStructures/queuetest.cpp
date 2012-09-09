#include "queuetest.h"
#include "DataStructures/preconditionviolation.h"
#include <QtTest/QtTest>
#include <iostream>

#define COMPARE_SIZE(m_queue, expected_size) QCOMPARE((int) (m_queue).size(), (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((int) (actual), (int) (expected))

using namespace DataStructures;

void QueueTest::init()
{
  m_queue = Queue<int>();
  for (int i = 0; i < 20; ++i) {
    m_queue.push_back(i);
  }
}

void QueueTest::test_default_constructor()
{
  Queue<int> queue1;
  QVERIFY2(queue1.empty(), "Default constructed Queue is not empty.");
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
  m_queue.push_back(20);
  COMPARE_SIZE(m_queue, 21);
  m_queue.push_back(222);
  COMPARE_SIZE(m_queue, 22);
  m_queue.pop_front();
  COMPARE_SIZE(m_queue, 21);
  m_queue.pop_front();
  COMPARE_SIZE(m_queue, 20);
  m_queue.pop_front();
  COMPARE_SIZE(m_queue, 19);
  m_queue.pop_front();
  COMPARE_SIZE(m_queue, 18);
  m_queue.push_back(22);
  COMPARE_SIZE(m_queue, 19);
}

void QueueTest::test_is_empty()
{
  for (int i = 0; i < 20; ++i) {
    QVERIFY(!m_queue.empty());
    m_queue.pop_front();
  }
  QVERIFY(m_queue.empty());
  Queue<int> queue2;
  QVERIFY(queue2.empty());
  queue2.push_back(2);
  QVERIFY(!queue2.empty());
  queue2.pop_front();
  QVERIFY(queue2.empty());
  Queue<int> queue3;
  queue3.push_back(2);
  QVERIFY(!queue3.empty());
  queue2.push_all(queue3.begin(), queue3.end());
  QVERIFY(!queue2.empty());
  queue2.pop_front();
  QVERIFY(queue2.empty());
  queue3.pop_front();
  QVERIFY(queue3.empty());
}

void QueueTest::test_index()
{
  int a = 333;
  try {
    m_queue[-1] = 5;
    QFAIL("m_queue[-1] didn't cause an exception.");
  } catch (PreconditionViolation e) { QCOMPARE(e.type(), OutOfRange); }
  try {
    a = m_queue[-1];
    QFAIL("a = m_queue[-1] didn't cause an exception.");
  } catch (PreconditionViolation e) { QCOMPARE(e.type(), OutOfRange); }
  try {
    m_queue[20] = 5;
    QFAIL("m_queue[-20] didn't cause an exception.");
  } catch (PreconditionViolation e) { QCOMPARE(e.type(), OutOfRange); }
  try {
    a = m_queue[20];
    QFAIL("a = m_queue[20] didn't cause an exception.");
  } catch (PreconditionViolation e) { QCOMPARE(e.type(), OutOfRange); }
  QCOMPARE(a, 333);
}

void QueueTest::test_push() {
  for (int i = 20; i < 25; ++i) {
    m_queue.push_back(i);
  }
  COMPARE_SIZE(m_queue, 25);
  for (int i = 0; i < 25; ++i) {
    QCOMPARE(m_queue[i], i);
  }
}

void QueueTest::test_pop() {
  for (int n = 0; n < 20; ++n) {
    QCOMPARE(m_queue.pop_front(), n);
    COMPARE_SIZE(m_queue, 19 - n);
    for (int i = 0; i < 19 - n; ++i) {
      QCOMPARE(m_queue[i], i + n + 1);
    }
  }
  try {
    m_queue.pop_front();
    QFAIL("Popping from an empty m_queue didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), EmptyList);
  }
}

void QueueTest::test_top() {
  for (int n = 0; n < 20; ++n) {
    QCOMPARE(m_queue.front(), n);
    m_queue.pop_front();
  }
  int a = 29;
  try {
    a = m_queue.front();
    QFAIL("Popping from an empty m_queue didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), EmptyList);
  }
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
  QVERIFY2(m_queue.empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push_back(22);
  m_queue.clear();
  QVERIFY2(m_queue.empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push_all(m_queue.begin(), m_queue.end());
  m_queue.clear();
  QVERIFY2(m_queue.empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push_back(22);
  m_queue.push_back(0);
  m_queue.clear();
  QVERIFY2(m_queue.empty(), "Emptied m_queue is not empty.");
  COMPARE_SIZE(m_queue, 0);
  m_queue.push_back(22);
}

void QueueTest::test_min_capacity()
{
  m_queue.min_capacity(55);
  COMPARE_INTS(m_queue.min_capacity(), 55);
}

void QueueTest::test_capacity()
{
  m_queue.min_capacity(46);
  QVERIFY(m_queue.capacity() >= 46);
  for (int i = 0; i < 100; ++i) {
    m_queue.push_back(0);
    QVERIFY(m_queue.capacity() >= 46);
  }
  for (int i = 0; i < 100; ++i) {
    m_queue.pop_front();
    QVERIFY(m_queue.capacity() >= 46);
  }
}


void QueueTest::test_equals()
{
  Queue<int> t1, t2;
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

void QueueTest::test_unequals()
{
  Queue<int> t1, t2;
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
