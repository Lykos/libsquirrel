#include "arithmetichelpertest.h"
#include "DataStructures/arithmetichelper.h"
#include "comparemacros.h"

using namespace DataStructures;
using namespace ArithmeticHelper;

void ArithmeticHelperTest::test_prev_pow2()
{
  COMPARE_INTS(prev_pow2(0), 0);
  for (int k = 0; k < 10; ++k) {
    for (int i = 1 << k; i < 1 << (k + 1); ++i) {
      COMPARE_INTS(prev_pow2(i), 1 << k);
    }
  }
}

void ArithmeticHelperTest::test_next_pow2()
{
  COMPARE_INTS(next_pow2(0), 0);
  COMPARE_INTS(next_pow2(1), 1);
  for (int k = 0; k < 10; ++k) {
    for (int i = (1 << k) + 1; i <= 1 << (k + 1); ++i) {
      COMPARE_INTS(next_pow2(i), 1 << (k + 1));
    }
  }
}
