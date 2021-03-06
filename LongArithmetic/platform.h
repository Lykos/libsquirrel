#ifndef LONGARITHMETIC_PLATFORM_H
#define LONGARITHMETIC_PLATFORM_H

#include <cstdint>
#include <climits>
#include <cstddef>
#include <cassert>

#define LONGINT64
#define USE_ASSEMBLY

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
#error One of LONGINT64, LONGINT32 or LONGINT16 has to be defined.
#endif
#endif
#endif

  typedef size_t size_type;

#define PART_SIZE (sizeof(part_type) * CHAR_BIT)

#define FLOAT_MANTISSA 23

#define DOUBLE_MANTISSA 53

#define FLOAT_EXPONENT (32 - FLOAT_MANTISSA - 1)

#define DOUBLE_EXPONENT (64 - DOUBLE_MANTISSA - 1)

#define FLOAT_BIAS 127

#define DOUBLE_BIAS 1023

}

#endif // LONGARITHMETIC_PLATFORM_H
