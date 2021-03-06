#ifndef LONGARITHMETIC_ALGEBRAHELPER_H
#define LONGARITHMETIC_ALGEBRAHELPER_H

namespace LongArithmetic {

  namespace AlgebraHelper {

    template <typename T, typename Structure>
    inline T inv_mod(const Structure* structure, const T& element, const T& modulus);

    template <typename T>
    inline T gcd(const T& first, const T& second);

    template <typename T, typename Structure>
    inline T& pow_eq(const Structure* structure, T& base, int64_t exponent);

    template <typename T, typename Structure>
    inline T& pow_mod_eq(const Structure* structure, T& base, const LongInt& exponent, const T& modulus);

  } // namespace AlgebraHelper
  
} // namespace LongArithmetic

#include "algebrahelper.hpp"

#endif // LONGARITHMETIC_ALGEBRAHELPER_H
