#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

#include <longint.h>
#include <iostream>
#include "add.h"

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline subtract(LongInt::part_type* a_begin,
                         LongInt::part_type* const a_end,
                         const LongInt::part_type* b_begin,
                         const LongInt::part_type* const b_end,
                         bool exchange)
    {
      assert(a_end >= a_begin);
      assert(b_end >= b_begin);
      assert(a_begin >= b_end || b_begin >= a_end);
      assert(a_end - a_begin >= b_end - b_begin);
      mpz_class ga = to_mpz(a_begin, a_end);
      mpz_class gb = to_mpz(b_begin, b_end);
      const LongInt::part_type* const old_a_begin = a_begin;
      if (exchange) {
        std::swap(ga, gb);
      }
      for (bool keep = false; keep || b_begin < b_end; ++a_begin, ++b_begin) {
        assert(a_begin < a_end); // Should never happen because a =< b
        LongInt::part_type left = *a_begin;
        LongInt::part_type right = b_begin < b_end ? *b_begin : 0;
        if (exchange) {
          std::swap(left, right);
        }
        if (keep) {
          asm("stc;\n"
          "\tsbbq %2, %0;\n"
          "\tsetc %1;\n"
          : "=g" (left), "=g" (keep) : "g" (right), "0" (left) : "cc");
        } else {
          asm("subq %2, %0;\n"
          "\tsetc %1;\n"
          : "=g" (left), "=g" (keep) : "g" (right), "0" (left) : "cc");
        }
        *a_begin = left;
      }
      mpz_class gc = to_mpz(old_a_begin, a_end);
      if (gc != ga - gb) {
        std::cout << "Should be a - b = " << ga << " - " << gb << " == " << ga - gb << " = c instead of " << gc << std::endl;
        assert(false);
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
