#ifndef QUEUETEST_H
#define QUEUETEST_H

#include <QObject>
#include "queue.h"

class QueueTest : public QObject
{
  Q_OBJECT

private:
  DataStructures::Queue<int> m_queue;

private Q_SLOTS:
  void init();

  void test_default_constructor();

  void test_copy_constructor();

  void test_push_all();

  void test_assign();

  void test_size();

  void test_is_empty();

  void test_index();

  void test_push();

  void test_top();

  void test_pop();

  void test_iterate();

  void test_clear();

  void test_next_higher();

  void test_next_lower();

  void test_min_capacity();

  void test_capacity();

  void test_equals();

  void test_unequals();

};

#endif // QUEUETEST_H
