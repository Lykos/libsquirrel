#ifndef AVLTREETEST_H
#define AVLTREETEST_H

#include "avltree.h"
#include "treetest.h"

class AVLTreeTest : public QObject, public TreeTest<DataStructures::AVLTree<int> >
{
  Q_OBJECT

private:
  typedef TreeTest<DataStructures::AVLTree<int> > Test;

private Q_SLOTS:
  void init() { Test::init(); }

  void test_empty_constructor() { Test::test_empty_constructor(); }

  void test_insert() { Test::test_insert(); }

  void test_search() { Test::test_search(); }

  // void test_remove() { Test::test_remove(); }

  void test_insert_all() { Test::test_insert_all(); }

  // void test_remove_all() { Test::test_remove_all(); }

  void test_clear() { Test::test_clear(); }

  void test_merge() { Test::test_merge(); }

  void test_copy_constructor() { Test::test_copy_constructor(); }

  void test_index() { Test::test_index(); }

  void test_const_index() { Test::test_const_index(); }

  void test_index_errors() { Test::test_index_errors(); }

  void test_const_index_errors() { Test::test_const_index_errors(); }

  void test_iterators() { Test::test_iterators(); }

  void test_const_iterators() { Test::test_const_iterators(); }

  void test_lower_bound() { Test::test_lower_bound(); }

  void test_lower_bound_const() { Test::test_lower_bound_const(); }

  void test_upper_bound() { Test::test_upper_bound(); }

  void test_upper_bound_const() { Test::test_upper_bound_const(); }

  void test_assign() { Test::test_assign(); }

  void test_equals() { Test::test_equals(); }

  void test_not_equals() { Test::test_not_equals(); }
};

#endif // AVLTREETEST_H
