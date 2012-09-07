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

  }

}

#endif // DATASTRUCTURES_PLATFORM_H
