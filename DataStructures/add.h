#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

#include "assembly.h"
#include "platform.h"

/*
 * Internal header, clients should not include. The code
 * appears in header so that inlining is possible.
 */
namespace DataStructures {

  namespace LongArithmetic {

    void inline add(part_type* a_begin,
                    part_type* a_end,
                    const part_type* b_begin,
                    const part_type* b_end)
    {
      arithmetic_assert(a_end - a_begin >= b_end - b_begin);
      for (bool keep = 0; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
        arithmetic_assert(a_begin < a_end);
        LongInt::part_type b_part = (b_begin < b_end ? *b_begin : 0);
        if (keep) {
          ASM_ADD_CARRY_SETCF(*a_begin, b_part, keep);
        } else {
          ASM_ADD_SETCF(*a_begin, b_part, keep);
        }
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
