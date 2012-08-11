#ifndef TESTTREAP_H
#define TESTTREAP_H

#include <QObject>
#include "treap.h"

class TreapTest : public QObject
{
  Q_OBJECT

private:
  void standard_fill(DataStructures::Treap<int>& t);

private Q_SLOTS:  
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
  
};

#endif // TESTTREAP_H
