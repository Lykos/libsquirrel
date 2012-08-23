#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "basetypes.h"
#include "longint.h"
#include <sstream>

namespace DataStructures {

  namespace ArithmeticHelper {

    template <typename T>
    inline T inv_mod(const T& element, const T& modulus);

    template <typename T>
    inline T gcd(const T& first, const T& second);

    template <typename T>
    T inv_mod(const T& element, const T &modulus)
    {
      T a (element);
      T b (modulus);
      T u_old = 0;
      T u = 1;
      T v_old = 1;
      T v = 0;
      while (b != 0) {
        T q;
        a.divide(b, q, a);
        u_old -= u * q;
        v_old -= v * q;
        std::swap(a, b);
        std::swap(u, u_old);
        std::swap(v, v_old);
      }
      if (a != 1) {
        std::ostringstream oss;
        oss << "element (" << element << ") and modulus (" << modulus << ") are not relatively prime, the gcd is " << a << ", hence no multiplicative inverse exists.";
        throw std::logic_error(oss.str());
      }
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
      while (b > 0) {
        a %= b;
        std::swap(a, b);
      }
      return a;
    }

    template <typename T>
    void pow_eq(T& base, index_type exponent)
    {
      T factor (base);
      T& result = base;
      result = base.one();
      for (unsigned int j = sizeof(index_type) * CHAR_BIT; j > 0;) {
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
    void pow_mod_eq(T& base, const LongInt& exponent, const LongInt& modulus)
    {
      T factor = (exponent >= LongInt::ZERO ? base : inv_mod(base, modulus));
      T& result = base;
      result = base.one();
      for (unsigned int j = sizeof(index_type) * CHAR_BIT; j > 0;) {
        --j;
        if (((exponent >> j) & LongInt::ONE) == LongInt::ONE) {
          result *= factor;
        }
        if (j > 0) {
          result *= result;
        }
        result %= modulus;
      }
    }

  }

}

#endif // ARITHMETIC_H
