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
      bool keep = 0;
      for (; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
        assert(a_begin < a_end);
        LongInt::part_type b_part = (b_begin < b_end ? *b_begin : 0);
        if (keep) {
          asm("stc;\n"
          "\tadcq %2, %0;\n"
          "\tsetc %1;"
          : "=q" (*a_begin), "=q" (keep) : "q" (b_part), "0" (*a_begin));
        } else {
          asm("addq %2, %0;\n"
          "\tsetc %1;\n"
          : "=q" (*a_begin), "=q" (keep) : "q" (b_part), "0" (*a_begin));
        }
      }
    }

    void inline add(LongInt::part_list::iterator a_begin,
                    LongInt::part_list::iterator a_end,
                    LongInt::part_list::const_iterator b_begin,
                    LongInt::part_list::const_iterator b_end)
    {
      add(&a_begin[0], &a_begin[0] + (a_end - a_begin), &b_begin[0], &b_begin[0] + (b_end - b_begin));
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
