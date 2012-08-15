#ifndef HEAPTEST_H
#define HEAPTEST_H

#include <QObject>
#include "heap.h"

class HeapTest : public QObject
{
  Q_OBJECT

private:
  DataStructures::Heap<int> m_heap;

private Q_SLOTS:
  void test_empty_constructor();

  void test_range_constructor();

  void test_copy_constructor();

  void test_push_all();

  void test_push();

  void test_pop();

  void test_top_const();

  void test_top();
};

#endif // HEAPTEST_H
