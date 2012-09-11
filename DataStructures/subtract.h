#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

#include "longint.h"

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline subtract(LongInt::part_type* tgt_begin,
                         LongInt::part_type* const tgt_end,
                         const LongInt::part_type* src_begin,
                         const LongInt::part_type* const src_end,
                         bool exchange);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "subtract.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
