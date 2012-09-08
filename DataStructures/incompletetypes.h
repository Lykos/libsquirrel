#ifndef DATASTRUCTURES_INCOMPLETETYPES_H
#define DATASTRUCTURES_INCOMPLETETYPES_H

#include <cstdint>

namespace DataStructures {

  class LongInt;

  class LongIntConverter;

  class UniformLongIntDistribution;

  template <typename T>
  class Ring;

  template <typename T, typename Structure>
  class Polynomial;

  namespace LongArithmetic {

    void divide(LongInt &dividend,
                LongInt &divisor,
                LongInt &quotient,
                LongInt &remainder,
                bool remainder_needed);

  }

  namespace AlgebraHelper {

    template <typename T, typename Structure>
    inline T inv_mod(const Structure* structure, const T& element, const T& modulus);

    template <typename T>
    inline T gcd(const T& first, const T& second);

    template <typename T, typename Structure>
    inline T& pow_eq(const Structure* structure, T& base, int64_t exponent);

    template <typename T, typename Structure>
    inline T& pow_mod_eq(const Structure* structure, T& base, const LongInt& exponent, const T& modulus);
  }

}

#endif // DATASTRUCTURES_INCOMPLETETYPES_H
