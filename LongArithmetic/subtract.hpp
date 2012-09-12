#ifndef LONGARITHMETIC_LONGARITHMETIC_SUBTRACT_HPP
#define LONGARITHMETIC_LONGARITHMETIC_SUBTRACT_HPP

#include "subtract.h"

// Internal header, clients should not include. Appears in header for inlining.
namespace LongArithmetic {

  namespace Operations {

    inline void subtract(part_type* tgt_begin,
                         part_type* const tgt_end,
                         const part_type* src_begin,
                         const part_type* const src_end,
                         bool exchange)
    {
      // Valid ranges
      arithmetic_assert(tgt_end >= tgt_begin);
      arithmetic_assert(src_end >= src_begin);
      // No aliasing
      arithmetic_assert(tgt_begin >= src_end || src_begin >= tgt_end);
      bool keep = false;
      while (src_begin < src_end && tgt_begin < tgt_end) {
        part_type left = exchange ? *src_begin : *tgt_begin;
        part_type right = exchange ? *tgt_begin : *src_begin;
        if (keep) {
          ASM_SUBTRACT_CARRY_SETCF(left, right, keep);
        } else {
          ASM_SUBTRACT_SETCF(left, right, keep);
        }
        *tgt_begin = left;
        ++tgt_begin;
        ++src_begin;
      }
      if (keep) {
        dec(tgt_begin, tgt_end);
      }
    }

  } // namespace LongArithmetic

} // namespace LongArithmetic

#endif // LONGARITHMETIC_LONGARITHMETIC_SUBTRACT_HPP
