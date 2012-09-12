#include <QtTest/QTest>
#include <cstdlib>
#include "longinttest.h"
#include "polynomialtest.h"
#include "finiteelementtest.h"

int main(int argc, char** argv) {
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);
  FiniteElementTest finite_element_test;
  QTest::qExec(&finite_element_test, argc, argv);
  PolynomialTest polynomial_test;
  QTest::qExec(&polynomial_test, argc, argv);
  return EXIT_SUCCESS;
}
