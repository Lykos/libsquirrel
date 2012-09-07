#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

#include "longint.h"
#include <gmpxx.h>
#include <iostream>

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    mpz_class to_mpz(const LongInt::part_type* begin, const LongInt::part_type* end);

    void inline add(LongInt::part_type* a_begin,
                    LongInt::part_type* a_end,
                    const LongInt::part_type* b_begin,
                    const LongInt::part_type* b_end)
    {
      assert(a_end - a_begin >= b_end - b_begin);
      LongInt::part_type* old_a_begin = a_begin;
      mpz_class a = to_mpz(a_begin, a_end);
      mpz_class b = to_mpz(b_begin, b_end);
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
      mpz_class r = to_mpz(old_a_begin, a_end);
      if (r != a + b) {
        std::cout << "Should be a + b = " << a << " + " << b << " == " << a + b << " instead of " << r << std::endl;
        assert(false);
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
