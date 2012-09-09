#ifndef QUEUETEST_H
#define QUEUETEST_H

#include <QtTest/QtTest>
#include "listtest.h"
#include "DataStructures/queue.h"

class QueueTest : public QObject, public ListTest<DataStructures::Queue>
{
  Q_OBJECT

private:
  typedef ListTest<DataStructures::Queue> Test;

public:
  QueueTest(): Test() {}

private Q_SLOTS:
  void init() { Test::init(); }

  void test_default_constructor() { Test::test_default_constructor(); }

  void test_copy_constructor() { Test::test_copy_constructor(); }

  void test_fill_constructor() { Test::test_fill_constructor(); }

  void test_assign_operator() { Test::test_assign_operator(); }

  void test_erase_index_range() { Test::test_erase_index_range(); }

  void test_erase_index_element() { Test::test_erase_index_element(); }

  void test_insert_index_range() { Test::test_insert_index_range(); }

  void test_insert_index_element() { Test::test_insert_index_element(); }

  void test_insert_index_fill() { Test::test_insert_index_fill(); }

  void test_erase_iterator_range() { Test::test_erase_iterator_range(); }

  void test_erase_iterator_element() { Test::test_erase_iterator_element(); }

  void test_insert_iterator_range() { Test::test_insert_iterator_range(); }

  void test_insert_iterator_element() { Test::test_insert_iterator_element(); }

  void test_insert_iterator_fill() { Test::test_insert_iterator_fill(); }

  void test_assign() { Test::test_assign(); }

  void test_size() { Test::test_size(); }

  void test_is_empty() { Test::test_is_empty(); }

  void test_index_errors() { Test::test_index_errors(); }

  void test_const_index_errors() { Test::test_const_index_errors(); }

  void test_push_back() { Test::test_push_back(); }

  void test_back() { Test::test_back(); }

  void test_push_front();

  void test_pop_front();

  void test_random_queueing();

  void test_pop_back() { Test::test_pop_back(); }

  void test_iterate() { Test::test_iterate(); }

  void test_clear() { Test::test_clear(); }

  void test_min_capacity() { Test::test_min_capacity(); }

  void test_capacity() { Test::test_capacity(); }

  void test_equals() { Test::test_equals(); }

  void test_unequals() { Test::test_unequals(); }

};

#endif // QUEUETEST_H
