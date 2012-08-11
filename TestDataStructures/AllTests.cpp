#include <QtTest/QTest>
#include <cstdlib>
#include "arraylisttest.h"
#include "longinttest.h"
#include "infiniterandomtest.h"
#include "treaptest.h"

int main(int argc, char** argv) {
  ArrayListTest array_list_test;
  QTest::qExec(&array_list_test, argc, argv);
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);
  InfiniteRandomTest infinite_random_test;
  QTest::qExec(&infinite_random_test, argc, argv);
  TreapTest treap_test;
  QTest::qExec(&treap_test);
  return EXIT_SUCCESS;
}
