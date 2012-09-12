#ifndef LONGARITHMETIC_ARITHMETIC_HPP
#define LONGARITHMETIC_ARITHMETIC_HPP

#include "arithmetichelper.h"
#include "assembly.h"
#include <cstdint>

namespace LongArithmetic {

  namespace ArithmeticHelper {

    inline uint64_t log2(uint64_t x)
    {
      if (x == 0) {
        return 0;
      }
      uint64_t result;
      ASM_BIT_SCAN(result, x);
      return result;
    }

  }

}

#endif // LONGARITHMETIC_ARITHMETIC_HPP
