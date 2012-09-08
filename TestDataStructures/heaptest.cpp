#include "heaptest.h"
#include "comparemacros.h"
#include "DataStructures/preconditionviolation.h"
#include <QtTest/QtTest>
#include <iostream>

using namespace DataStructures;

void HeapTest::test_empty_constructor()
{
  Heap<int> h;
  COMPARE_SIZE(h, 0);
}

void HeapTest::test_range_constructor()
{
  int a[] {1, 3, 5, 4, 2, 2};
  Heap<int> h (a + 0, a + 6);
  COMPARE_SIZE(h, 6);
  COMPARE_INTS(h.pop(), 1);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 3);
  COMPARE_INTS(h.pop(), 4);
  COMPARE_INTS(h.pop(), 5);
}

void HeapTest::test_copy_constructor()
{
  Heap<int> h;
  h.push(4);
  h.push(1);
  h.push(2);
  h.push(3);
  h.push(2);
  h.push(5);
  Heap<int> h2 (h);
  COMPARE_SIZE(h2, 6);
  COMPARE_INTS(h2.pop(), 1);
  COMPARE_INTS(h2.pop(), 2);
  COMPARE_INTS(h2.pop(), 2);
  COMPARE_INTS(h2.pop(), 3);
  COMPARE_INTS(h2.pop(), 4);
  COMPARE_INTS(h2.pop(), 5);
}

void HeapTest::test_push_all()
{
  int a[] {1, 3, 5, 4, 2, 2};
  Heap<int> h;
  h.push_all(a + 0, a + 6);
  COMPARE_SIZE(h, 6);
  COMPARE_INTS(h.pop(), 1);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 3);
  COMPARE_INTS(h.pop(), 4);
  COMPARE_INTS(h.pop(), 5);
}

void HeapTest::test_push()
{
  Heap<int> h;
  h.push(5);
  COMPARE_SIZE(h, 1);
  COMPARE_INTS(h.top(), 5);
  h.push(3);
  COMPARE_SIZE(h, 2);
  COMPARE_INTS(h.top(), 3);
  h.push(2);
  COMPARE_SIZE(h, 3);
  COMPARE_INTS(h.top(), 2);
  h.push(6);
  COMPARE_SIZE(h, 4);
  COMPARE_INTS(h.top(), 2);
  h.push(2);
  COMPARE_SIZE(h, 5);
  COMPARE_INTS(h.top(), 2);
  h.push(1);
  COMPARE_SIZE(h, 6);
  COMPARE_INTS(h.top(), 1);
  COMPARE_INTS(h.pop(), 1);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_INTS(h.pop(), 3);
  COMPARE_INTS(h.pop(), 5);
  COMPARE_INTS(h.pop(), 6);
}

void HeapTest::test_pop()
{
  int a[] {1, 3, 5, 4, 2, 2};
  Heap<int> h (a + 0, a + 6);
  COMPARE_INTS(h.top(), 1);
  COMPARE_INTS(h.pop(), 1);
  COMPARE_SIZE(h, 5);
  COMPARE_INTS(h.top(), 2);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_SIZE(h, 4);
  COMPARE_INTS(h.top(), 2);
  COMPARE_INTS(h.pop(), 2);
  COMPARE_SIZE(h, 3);
  COMPARE_INTS(h.top(), 3);
  COMPARE_INTS(h.pop(), 3);
  COMPARE_SIZE(h, 2);
  COMPARE_INTS(h.top(), 4);
  COMPARE_INTS(h.pop(), 4);
  COMPARE_SIZE(h, 1);
  COMPARE_INTS(h.top(), 5);
  COMPARE_INTS(h.pop(), 5);
  COMPARE_SIZE(h, 0);
  int b = 4343;
  try {
    b = h.pop();
    QFAIL("Popping from an empty heap didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  COMPARE_INTS(b, 4343);
}

void HeapTest::test_top()
{
  int a[] {1, 3, 5, 4, 2, 2};
  Heap<int> h (a + 0, a + 6);
  COMPARE_INTS(h.top(), 1);
  h.pop();
  COMPARE_SIZE(h, 5);
  COMPARE_INTS(h.top(), 2);
  h.pop();
  COMPARE_SIZE(h, 4);
  COMPARE_INTS(h.top(), 2);
  h.pop();
  COMPARE_SIZE(h, 3);
  COMPARE_INTS(h.top(), 3);
  h.pop();
  COMPARE_SIZE(h, 2);
  COMPARE_INTS(h.top(), 4);
  h.pop();
  COMPARE_SIZE(h, 1);
  COMPARE_INTS(h.top(), 5);
  h.pop();
  COMPARE_SIZE(h, 0);
  int b = 4343;
  try {
    b = h.top();
    QFAIL("Taking the top from an empty heap didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  COMPARE_INTS(b, 4343);
}

void HeapTest::test_top_const()
{
  int a[] {1, 3, 5, 4, 2, 2};
  Heap<int> h2 (a + 0, a + 6);
  const Heap<int>& h = h2;
  COMPARE_INTS(h.top(), 1);
  h2.pop();
  COMPARE_SIZE(h, 5);
  COMPARE_INTS(h.top(), 2);
  h2.pop();
  COMPARE_SIZE(h, 4);
  COMPARE_INTS(h.top(), 2);
  h2.pop();
  COMPARE_SIZE(h, 3);
  COMPARE_INTS(h.top(), 3);
  h2.pop();
  COMPARE_SIZE(h, 2);
  COMPARE_INTS(h.top(), 4);
  h2.pop();
  COMPARE_SIZE(h, 1);
  COMPARE_INTS(h.top(), 5);
  h2.pop();
  COMPARE_SIZE(h, 0);
  int b = 4343;
  try {
    b = h.top();
    QFAIL("Taking the top from an empty const Heap didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), OutOfRange);
  }
  COMPARE_INTS(b, 4343);
}
