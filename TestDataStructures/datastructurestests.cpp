#include <QtTest/QTest>
#include <cstdlib>
#include "arraylisttest.h"
#include "longinttest.h"
#include "infiniterandomtest.h"
#include "binarytreetest.h"
#include "treaptest.h"
#include "avltreetest.h"
#include "queuetest.h"
#include "heaptest.h"

int main(int argc, char** argv) {/*
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);*/
  ArrayListTest array_list_test;
  QTest::qExec(&array_list_test, argc, argv);
  InfiniteRandomTest infinite_random_test;
  QTest::qExec(&infinite_random_test, argc, argv);
  BinaryTreeTest base_tree_test;
  QTest::qExec(&base_tree_test, argc, argv);
  TreapTest treap_test;
  QTest::qExec(&treap_test, argc, argv);
  AVLTreeTest avl_tree_test;
  QTest::qExec(&avl_tree_test, argc, argv);
  QueueTest queue_test;
  QTest::qExec(&queue_test, argc, argv);
  HeapTest heap_test;
  QTest::qExec(&heap_test, argc, argv);
  return EXIT_SUCCESS;
}
