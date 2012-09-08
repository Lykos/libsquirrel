#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

#include "longint.h"

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline subtract(LongInt::part_type* a_begin,
                         LongInt::part_type* const a_end,
                         const LongInt::part_type* b_begin,
                         const LongInt::part_type* const b_end,
                         bool exchange);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "subtract.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
