#ifndef ARITHMETIC_H
#define ARITHMETIC_H

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

    inline uint64_t log2(uint64_t x)
    {
      if (x == 0) {
        return 0;
      }
      uint64_t result;
      asm ( "\tbsrq %1, %0\n"
            : "=r"(result)
            : "r" (x)
        );
      return result;
    }

  }

}

#endif // ARITHMETIC_H
