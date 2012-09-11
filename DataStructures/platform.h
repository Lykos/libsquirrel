#ifndef DATASTRUCTURES_PLATFORM_H
#define DATASTRUCTURES_PLATFORM_H

#include <cstdint>
#include <climits>
#include <cstddef>

#define ARITHMETIC_DEBUG

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

#define LONGINT64
#define USE_ASSEMBLY

// Internal header for platform dependent typedefs and constants
namespace DataStructures {

  namespace LongArithmetic {

#ifdef LONGINT64
    typedef uint64_t part_type;
#else
#ifdef LONGINT32
    typedef uint32_t part_type;
#else
#ifdef LONGINT16
    typedef uint16_t part_type;
#else
#ifdef LONGINT8
    typedef uint8_t part_type;
#else
#error One of LONGINT64 LONGINT32 LONGINT16 or LONGINT8 has to be defined.
#endif
#endif
#endif
#endif

    typedef size_t size_type;

    const uint_fast16_t PART_SIZE = sizeof(part_type) * CHAR_BIT;

    const uint_fast16_t FLOAT_MANTISSA = 23;

    const uint_fast16_t DOUBLE_MANTISSA = 53;

    const uint_fast16_t FLOAT_EXPONENT = 32 - FLOAT_MANTISSA - 1;

    const uint_fast16_t DOUBLE_EXPONENT = 64 - DOUBLE_MANTISSA - 1;

    const uint_fast16_t FLOAT_BIAS = 127;

    const uint_fast16_t DOUBLE_BIAS = 1023;
  }

}

#endif // DATASTRUCTURES_PLATFORM_H
