#include "heaparithmetictest.h"
#include "DataStructures/heaparithmetic.h"
#include "comparemacros.h"

using namespace DataStructures;
using namespace HeapArithmetic;

void HeapArithmeticTest::test_parent()
{
  COMPARE_INTS(HeapArithmetic::parent(1), 0);
  COMPARE_INTS(HeapArithmetic::parent(2), 0);

  COMPARE_INTS(HeapArithmetic::parent(3), 1);
  COMPARE_INTS(HeapArithmetic::parent(4), 1);
  COMPARE_INTS(HeapArithmetic::parent(5), 2);
  COMPARE_INTS(HeapArithmetic::parent(6), 2);

  COMPARE_INTS(HeapArithmetic::parent(7), 3);
  COMPARE_INTS(HeapArithmetic::parent(8), 3);
  COMPARE_INTS(HeapArithmetic::parent(9), 4);
  COMPARE_INTS(HeapArithmetic::parent(10), 4);
  COMPARE_INTS(HeapArithmetic::parent(11), 5);
  COMPARE_INTS(HeapArithmetic::parent(12), 5);
  COMPARE_INTS(HeapArithmetic::parent(13), 6);
  COMPARE_INTS(HeapArithmetic::parent(14), 6);
}

void HeapArithmeticTest::test_left_child()
{
  COMPARE_INTS(left_child(0), 1);

  COMPARE_INTS(left_child(1), 3);
  COMPARE_INTS(left_child(2), 5);

  COMPARE_INTS(left_child(3), 7);
  COMPARE_INTS(left_child(4), 9);
  COMPARE_INTS(left_child(5), 11);
  COMPARE_INTS(left_child(6), 13);

  COMPARE_INTS(left_child(7), 15);
  COMPARE_INTS(left_child(8), 17);
  COMPARE_INTS(left_child(9), 19);
  COMPARE_INTS(left_child(10), 21);
  COMPARE_INTS(left_child(11), 23);
  COMPARE_INTS(left_child(12), 25);
  COMPARE_INTS(left_child(13), 27);
  COMPARE_INTS(left_child(14), 29);
}

void HeapArithmeticTest::test_right_child()
{
  COMPARE_INTS(right_child(0), 2);

  COMPARE_INTS(right_child(1), 4);
  COMPARE_INTS(right_child(2), 6);

  COMPARE_INTS(right_child(3), 8);
  COMPARE_INTS(right_child(4), 10);
  COMPARE_INTS(right_child(5), 12);
  COMPARE_INTS(right_child(6), 14);

  COMPARE_INTS(right_child(7), 16);
  COMPARE_INTS(right_child(8), 18);
  COMPARE_INTS(right_child(9), 20);
  COMPARE_INTS(right_child(10), 22);
  COMPARE_INTS(right_child(11), 24);
  COMPARE_INTS(right_child(12), 26);
  COMPARE_INTS(right_child(13), 28);
  COMPARE_INTS(right_child(14), 30);
}
