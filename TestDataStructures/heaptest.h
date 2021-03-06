#ifndef HEAPTEST_H
#define HEAPTEST_H

#include <QObject>
#include "DataStructures/heap.h"

class HeapTest : public QObject
{
  Q_OBJECT

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
