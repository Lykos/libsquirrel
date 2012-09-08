#ifndef DATASTRUCTURES_PLATFORM_H
#define DATASTRUCTURES_PLATFORM_H

#include <stdint.h>

/*
 * Assertions for internal consistency checks.
 * May be very inefficient and hence they are usually disabled, but
 * they can be turned on to help to track down bugs faster.
 */
#ifdef ARITHMETIC_DEBUG
#define arithmetic_assert(b) assert(b)
#else
#define arithmetic_assert(b)
#endif

// Internal header for platform dependent typedefs and constants
namespace DataStructures {

  namespace LongArithmetic {

    typedef uint64_t part_type;

    const uint_fast16_t FLOAT_MANTISSA = 23;

    const uint_fast16_t DOUBLE_MANTISSA = 53;

    const uint_fast16_t FLOAT_EXPONENT = 32 - FLOAT_MANTISSA - 1;

    const uint_fast16_t DOUBLE_EXPONENT = 64 - DOUBLE_MANTISSA - 1;

    const uint_fast16_t FLOAT_BIAS = 127;

    const uint_fast16_t DOUBLE_BIAS = 1023;
  }

}

#endif // DATASTRUCTURES_PLATFORM_H
