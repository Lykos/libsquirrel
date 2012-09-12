#ifndef DATASTRUCTURES_ARITHMETIC_HPP
#define DATASTRUCTURES_ARITHMETIC_HPP

#include "arithmetichelper.h"
#include <cstdint>

namespace DataStructures {

  namespace ArithmeticHelper {

    // The functions are defined in the header so that the compiler can inline them

    inline uint64_t next_pow2(uint64_t x)
    {
      x -= 1;
      x |= (x >> 1);
      x |= (x >> 2);
      x |= (x >> 4);
      x |= (x >> 8);
      x |= (x >> 16);
      x |= (x >> 32);
      return ++x;
    }

    inline uint64_t prev_pow2(uint64_t x)
    {
      x |= (x >> 1);
      x |= (x >> 2);
      x |= (x >> 4);
      x |= (x >> 8);
      x |= (x >> 16);
      return ++x >> 1;
    }

  }

}

#endif // DATASTRUCTURES_ARITHMETIC_HPP
