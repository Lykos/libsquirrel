#include <QtTest/QTest>
#include <cstdlib>
#include "longinttest.h"
#include "finiteelementtest.h"
#include "polynomialtest.h"
#include "arraylisttest.h"
#include "infiniterandomtest.h"
#include "treaptest.h"
#include "avltreetest.h"
#include "queuetest.h"
#include "arithmetichelpertest.h"
#include "heaparithmetictest.h"
#include "heaptest.h"

int main(int argc, char** argv) {
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);
  FiniteElementTest finite_element_test;
  QTest::qExec(&finite_element_test, argc, argv);
  PolynomialTest polynomial_test;
  QTest::qExec(&polynomial_test, argc, argv);
  ArrayListTest array_list_test;
  QTest::qExec(&array_list_test, argc, argv);
  InfiniteRandomTest infinite_random_test;
  QTest::qExec(&infinite_random_test, argc, argv);
  TreapTest treap_test;
  QTest::qExec(&treap_test, argc, argv);
  AVLTreeTest avl_tree_test;
  QTest::qExec(&avl_tree_test, argc, argv);
  QueueTest queue_test;
  QTest::qExec(&queue_test, argc, argv);
  ArithmeticHelperTest arithmetic_helper_test;
  QTest::qExec(&arithmetic_helper_test, argc, argv);
  HeapArithmeticTest heap_arithmetic_test;
  QTest::qExec(&heap_arithmetic_test, argc, argv);
  HeapTest heap_test;
  QTest::qExec(&heap_test, argc, argv);
  return EXIT_SUCCESS;
}
