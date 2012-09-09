#ifndef TESTTREAP_H
#define TESTTREAP_H

#include "DataStructures/conditiontype.h"
#include "DataStructures/preconditionviolation.h"
#include "treetest.h"
#include <QObject>
#include <QtTest/QtTest>
#include <iostream>

template <template <typename T> class Tree>
class TreeTest
{
private:
  Tree<int> m_tree;

  void standard_fill(Tree<int>& tree);

protected:
  void init();

  void test_empty_constructor();

  void test_insert();

  void test_search();

  void test_remove();

  void test_insert_all();

  void test_remove_all();

  void test_clear();

  void test_merge();

  void test_copy_constructor();

  void test_index();

  void test_const_index();

  void test_index_errors();

  void test_const_index_errors();

  void test_iterators();

  void test_const_iterators();

  void test_lower_bound();

  void test_lower_bound_const();

  void test_upper_bound();

  void test_upper_bound_const();

  void test_assign();

  void test_equals();

  void test_not_equals();

};

#include "treetest.hpp"

#endif // TESTTREAP_H
