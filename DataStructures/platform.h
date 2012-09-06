#ifndef DATASTRUCTURES_LONGARITHMETIC_ASSEMBLY_H
#define DATASTRUCTURES_LONGARITHMETIC_ASSEMBLY_H

#include <stdint.h>

// Internal header, clients should not include. Appears in header for inlining.
// Contains all the platform dependent code needed for LongInt
// ArithmeticHelper may contain platform dependent code, too.
namespace DataStructures {

  namespace LongArithmetic {

    typedef uint64_t part_type;
    
  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ASSEMBLY_H
