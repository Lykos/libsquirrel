#ifndef DATASTRUCTURES_ALGEBRAHELPER_HPP
#define DATASTRUCTURES_ALGEBRAHELPER_HPP

#include "algebrahelper.h"
#include "longint.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include <climits>
#include <cstdint>
#include <stdexcept>

namespace DataStructures {

  namespace AlgebraHelper {

    template <typename T, typename Structure>
    inline T inv_mod(const Structure* structure, const T& element, const T &modulus)
    {
      T a (modulus);
      T b (element);
      T u_old = structure->zero();
      T u = modulus.one();
      while (b != structure->zero()) {
        T q;
        a.divide(b, q, a);
        u_old -= u * q;
        std::swap(a, b);
        std::swap(u, u_old);
      }
      PREC(NotRelativelyPrime, a == structure->one());
      u_old += modulus;
      u_old %= modulus;
      return u_old;
    }

    template <typename T>
    T gcd(const T &first, const T &second)
    {
      T a = first;
      T b = second;
      while (b != b.zero()) {
        a %= b;
        std::swap(a, b);
      }
      return a;
    }

    template <typename T, typename Structure>
    inline T& pow_eq(const Structure* structure, T& base, int64_t exponent)
    {
      // It is probably safer to use a signed type and check >= 0 than to use an unsigned type.
      PREC(NegativeExponent, exponent >= 0);
      T factor (base);
      T& result = base;
      result = structure->one();
      for (uint_fast16_t j = sizeof(int64_t) * CHAR_BIT; j > 0;) {
        --j;
        if ((exponent >> j) & 1) {
          result *= factor;
        }
        if (j > 0) {
          result *= result;
        }
      }
      return result;
    }

    template <typename T, typename Structure>
    inline T& pow_mod_eq(const Structure* structure, T& base, const LongInt& exponent, const T& modulus)
    {
      T factor = (exponent.positive() ? base : inv_mod(structure, base, modulus));
      T& result = base;
      result = structure->one();
      for (ulong i = exponent.size(); i > 0;) {
        --i;
        LongInt::part_type exponent_part = exponent.part_at(i);
        for (uint_fast16_t j = sizeof(LongInt::part_type) * CHAR_BIT; j > 0;) {
          --j;
          if ((exponent_part >> j) & 1) {
            result *= factor;
          }
          if (j > 0 || i > 0) {
            result *= result;
          }
          result %= modulus;
        }
      }
      return result;
    }

  } // namespace AlgebraHelper
  
} // namespace DataStructures

#endif // DATASTRUCTURES_ALGEBRAHELPER_HPP
