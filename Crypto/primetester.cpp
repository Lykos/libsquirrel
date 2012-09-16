#include "primetester.h"
#include "LongArithmetic/algebrahelper.h"
#include <boost/random/mersenne_twister.hpp>

namespace Crypto {

  using namespace LongArithmetic;

  using namespace AlgebraHelper;

  static const LongInt MINUS_ONE = -1;

  static const LongInt ZERO = 0;

  static const LongInt ONE = 1;

  static const LongInt TWO = 2;

  bool PrimeTester::is_prime(const LongInt& number, number_size_t security)
  {
    // We have 1/4 fail probability in each step
    number_size_t repetitions = (security >> 1) + 1;
    LongInt n = number.abs();
    if (n < TWO) {
      return false;
    } else if (n == TWO) {
      return true;
    } else if ((n & ONE) == ZERO) {
      return false;
    }
    UniformLongIntDistribution a_dist (2, n - ONE);
    for (number_size_t i = 0; i < repetitions; ++i) {
      LongInt a = a_dist(m_random_generator);
      if (gcd(a, number) != ONE) {
        return false;
      }
      number_size_t j = 1;
      LongInt minus_one = n - ONE;
      LongInt d = minus_one >> 1;
      while ((d & ONE) == ZERO) {
        ++j;
        d >>= 1;
      }
      a.pow_mod_eq(d, n);
      if (a != ONE) {
        bool was_minus_one = false;
        for (number_size_t r = 0; r < j; ++r, a = (a * a) % n) {
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
