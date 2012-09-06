#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

#include <longint.h>

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline subtract(LongInt::part_type* a_begin,
                         LongInt::part_type*  a_end,
                         const LongInt::part_type*  b_begin,
                         const LongInt::part_type*  b_end,
                         bool exchange)
    {
      assert(a_end - a_begin >= b_end - b_begin);
      for (bool keep = false; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
        assert(a_begin < a_end); // Should never happen because a =< b
        LongInt::part_type left = *a_begin;
        LongInt::part_type right = b_begin < b_end ? *b_begin : 0l;
        if (exchange) {
          std::swap(left, right);
        }
        if (keep) {
          asm("stc;\n"
          "\tsbbq %2, %0;\n"
          "\tsetc %1;"
          : "=q" (*a_begin), "=q" (keep) : "q" (right), "0" (left) : "cc");
        } else {
          asm("subq %2, %0;\n"
          "\tsetc %1;\n"
          : "=q" (*a_begin), "=q" (keep) : "q" (right), "0" (left) : "cc");
        }
      }
    }

    void inline subtract(const LongInt::part_list::iterator& a_begin,
                         const LongInt::part_list::iterator& a_end,
                         const LongInt::part_list::const_iterator& b_begin,
                         const LongInt::part_list::const_iterator& b_end,
                         bool exchange)
    {
      subtract(&a_begin[0], &a_begin[0] + (a_end - a_begin), &b_begin[0], &b_begin[0] + (b_end - b_begin), exchange);
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
