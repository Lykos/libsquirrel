#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

#include "longint.h"

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline add(LongInt::part_type* a_begin,
                    LongInt::part_type* a_end,
                    const LongInt::part_type* b_begin,
                    const LongInt::part_type* b_end)
    {
      assert(a_end - a_begin >= b_end - b_begin);
      for (bool keep = 0; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
        assert(a_begin < a_end);
        LongInt::part_type b_part = (b_begin < b_end ? *b_begin : 0);
        if (keep) {
          asm("\tstc;\n"
              "\tadcq %2, %0;\n"
              "\tsetc %1;"
          : "=g" (*a_begin), "=g" (keep) : "r" (b_part), "0" (*a_begin) : "cc");
        } else {
          asm("\taddq %2, %0;\n"
              "\tsetc %1;\n"
          : "=g" (*a_begin), "=g" (keep) : "r" (b_part), "0" (*a_begin) : "cc");
        }
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
