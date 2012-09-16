#ifndef FIBONACCIHEAPTEST_H
#define FIBONACCIHEAPTEST_H

#include "DataStructures/fibonacciheap.h"
#include <QObject>

class FibonacciHeapTest : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void test_empty_constructor();

  void test_range_constructor();

  void test_copy_constructor();

  void test_remove();

  void test_decrease_key();

  void test_push();

  void test_pop();

  void test_top_const();

  void test_top();

};

#endif // FIBONACCIHEAPTEST_H
