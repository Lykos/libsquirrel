#ifndef DATASTRUCTURES_ALGEBRAHELPER_H
#define DATASTRUCTURES_ALGEBRAHELPER_H

#include "longint.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include <climits>
#include <cstdint>
#include <sstream>
#include <stdexcept>

namespace DataStructures {

  namespace AlgebraHelper {

    template <typename T>
    inline T inv_mod(const T& element, const T& modulus);

    template <typename T>
    inline T gcd(const T& first, const T& second);

    template <typename T>
    T inv_mod(const T& element, const T &modulus)
    {
      T a (modulus);
      T b (element);
      T u_old = modulus.zero();
      T u = modulus.one();
      while (b != modulus.zero()) {
        T q;
        a.divide(b, q, a);
        u_old -= u * q;
        std::swap(a, b);
        std::swap(u, u_old);
      }
      PREC(NotRelativelyPrime, a == modulus.one());
      u_old += modulus;
      u_old %= modulus;
      return u_old;
    }

    template <typename T>
    T gcd(const T &first, const T &second)
    {
      T a = first.abs();
      T b = second.abs();
      if (first < second) {
        std::swap(a, b);
      }
      while (b != b.zero()) {
        a %= b;
        std::swap(a, b);
      }
      return a;
    }

    template <typename T>
    void pow_eq(T& base, u_int64_t exponent)
    {
      T factor (base);
      T& result = base;
      result = base.one();
      for (u_int8_t j = sizeof(u_int64_t) * CHAR_BIT; j > 0;) {
        --j;
        if ((exponent >> j) & 1) {
          result *= factor;
        }
        if (j > 0) {
          result *= result;
        }
      }
    }

    template <typename T>
    void pow_mod_eq(T& base, const LongInt& exponent, const T& modulus)
    {
      T factor = (exponent.positive() ? base : inv_mod(base, modulus));
      T& result = base;
      result = base.one();
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
    }

  } // namespace AlgebraHelper
  
} // namespace DataStructures

#endif // DATASTRUCTURES_ALGEBRAHELPER_H
