#include "fibonacciheaptest.h"
#include "comparemacros.h"
#include <iostream>

using namespace std;
using namespace DataStructures;

void FibonacciHeapTest::test_empty_constructor()
{
  FibonacciHeap<int> fheap;
  COMPARE_SIZE(fheap, 0);
  QVERIFY2(fheap.empty(), "Empty constructed heap is not empty.");
}

void FibonacciHeapTest::test_range_constructor()
{
  int a[] = {5, 32, 6, 2};
  FibonacciHeap<int> fheap (a + 0, a + 4);
  COMPARE_SIZE(fheap, 4);
  QCOMPARE(fheap.top(), 2);
}

void FibonacciHeapTest::test_copy_constructor()
{
  FibonacciHeap<int> fheap {1, 2, 3, 5, 4};
  //FibonacciHeap<int> copy (fheap);
  //QCOMPARE(copy.size(), fheap.size());
  //QCOMPARE(copy.top(), fheap.top());
}

void FibonacciHeapTest::test_remove()
{
  FibonacciHeap<int> fheap {17, 2, 3, 5, 4};
  FibonacciHeap<int>::node_pointer handle = fheap.push(1);
  fheap.remove(handle);
  COMPARE_SIZE(fheap, 5);
  QCOMPARE(fheap.top(), 2);
}

void FibonacciHeapTest::test_decrease_key()
{
  FibonacciHeap<int> fheap {2, 3, 5, 4};
  FibonacciHeap<int>::node_pointer handle = fheap.push(17);
  fheap.decrease_key(handle);
}

void FibonacciHeapTest::test_push()
{
  FibonacciHeap<int> fheap {2, 3, 5, 4};
  fheap.push(17);
  QCOMPARE(fheap.top(), 2);
  fheap.push(1);
  QCOMPARE(fheap.top(), 1);
}

void FibonacciHeapTest::test_pop()
{
  FibonacciHeap<int> fheap {2, 3, 5, 4, 19, 6};
  QCOMPARE(fheap.pop(), 2);
  QCOMPARE(fheap.top(), 3);
  QCOMPARE(fheap.pop(), 3);
  QCOMPARE(fheap.top(), 4);
  QCOMPARE(fheap.pop(), 4);
  QCOMPARE(fheap.top(), 5);
  QCOMPARE(fheap.pop(), 5);
  QCOMPARE(fheap.top(), 6);
  QCOMPARE(fheap.pop(), 6);
  QCOMPARE(fheap.top(), 19);
  QCOMPARE(fheap.pop(), 19);
}

void FibonacciHeapTest::test_top_const()
{
  FibonacciHeap<int> fheap {2, 3, 5, 4, 19, 6};
  const FibonacciHeap<int>& fheap2 = fheap;
  QCOMPARE(fheap2.top(), 2);
}

void FibonacciHeapTest::test_top()
{
  FibonacciHeap<int> fheap {2, 3, 5, 4, 19, 6};
  QCOMPARE(fheap.top(), 2);
}
