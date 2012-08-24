#include "primetester.h"
#include "arithmetichelper.h"

using namespace DataStructures::ArithmeticHelper;

namespace Crypto {

  static const DataStructures::LongInt MINUS_ONE = -1;

  static const DataStructures::LongInt ZERO = 0;

  static const DataStructures::LongInt ONE = 1;

  static const DataStructures::LongInt TWO = 2;

  DataStructures::LongInt PrimeTester::random_prime(DataStructures::index_type number_bits) const
  {
    DataStructures::LongInt result = 1;
    do {
      result = DataStructures::rand_bits(number_bits);
    } while (!is_prime(result, number_bits + 10));
    return result;
  }

  bool PrimeTester::is_prime(const DataStructures::LongInt& number, DataStructures::index_type security) const
  {
    // We have 1/4 fail probability in each step
    DataStructures::index_type repetitions = (security >> 1) + 1;
    typedef DataStructures::LongInt Int;
    Int n = number.abs();
    if (n < TWO) {
      return false;
    } else if (n == TWO) {
      return true;
    } else if ((n & ONE) == ZERO) {
      return false;
    }
    for (DataStructures::index_type i = 0; i < repetitions; ++i) {
      Int a = rand_number(n - 2) + 2;
      if (gcd(a, number) != ONE) {
        return false;
      }
      DataStructures::index_type j = 1;
      Int minus_one = n - ONE;
      Int d = minus_one >> 1;
      while ((d & ONE) == ZERO) {
        ++j;
        d >>= 1;
      }
      a.pow_mod_eq(d, n);
      if (a != ONE) {
        bool was_minus_one = false;
        for (DataStructures::index_type r = 0; r < j; ++r, a = (a * a) % n) {
          if (a == minus_one) {
            was_minus_one = true;
            break;
          }
        }
        if (!was_minus_one && a != minus_one) {
          return false;
        }
      }
    }
    return true;
  }

}
