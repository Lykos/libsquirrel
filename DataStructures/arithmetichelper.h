#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <cstdint>

namespace DataStructures {

  namespace ArithmeticHelper {

    inline uint64_t next_pow2(uint64_t x);

    inline uint64_t prev_pow2(uint64_t x);

    inline uint64_t log2(uint64_t x);

  }

}

#include "arithmetichelper.hpp"

#endif // ARITHMETIC_H
