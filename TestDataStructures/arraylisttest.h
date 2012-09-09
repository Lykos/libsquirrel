#ifndef ARRAYLISTTEST_H
#define ARRAYLISTTEST_H
#include <QtTest/QtTest>
#include "DataStructures/arraylist.h"

class ArrayListTest : public QObject
{
  Q_OBJECT

public:
  ArrayListTest();

private:
  DataStructures::ArrayList<int> list;

private Q_SLOTS:
  void init();

  void test_default_constructor();

  void test_fill_constructor();

  void test_copy_constructor();

  void test_erase_index_range();

  void test_erase_index_element();

  void test_insert_index_range();

  void test_insert_index_element();

  void test_insert_index_fill();

  void test_erase_iterator_range();

  void test_erase_iterator_element();

  void test_insert_iterator_range();

  void test_insert_iterator_element();

  void test_insert_iterator_fill();

  void test_assign();

  void test_size();

  void test_is_empty();

  void test_index_errors();

  void test_const_index_errors();

  void test_push();

  void test_top();

  void test_pop();

  void test_iterate();

  void test_clear();

  void test_min_capacity();

  void test_capacity();

  void test_equals();

  void test_unequals();

};

#endif // ARRAYLISTTEST_H
