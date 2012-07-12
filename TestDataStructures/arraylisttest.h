#ifndef ARRAYLISTTEST_H
#define ARRAYLISTTEST_H
#include <QtTest/QtTest>
#include "arraylist.h"

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
  void test_range_copy_constructor();
  void test_assign();
  void test_plus();
  void test_plus_assign();
  void test_times();
  void test_times_assign();
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
};

#endif // ARRAYLISTTEST_H
