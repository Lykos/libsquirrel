#include "arraylisttest.h"
#include "longinttest.h"
#include <QtTest/QTest>

int main(int argc, char** argv) {
  ArrayListTest array_list_test;
  QTest::qExec(&array_list_test, argc, argv);
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);
}
