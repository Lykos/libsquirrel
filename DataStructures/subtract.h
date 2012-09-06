#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline subtract(const LongInt::part_list::iterator& a_begin,
                         const LongInt::part_list::iterator& a_end,
                         const LongInt::part_list::const_iterator& b_begin,
                         const LongInt::part_list::const_iterator& b_end,
                         bool exchange)
    {
      bool keep = false;
      LongInt::part_list::iterator a_it (a_begin);
      for (LongInt::part_list::const_iterator b_it (b_begin); keep == 1 || b_it < b_end; ++a_it, ++b_it) {
        assert(a_it < a_end); // Should never happen because a < b
        LongInt::part_type left = *a_it;
        LongInt::part_type right = b_it < b_end ? *b_it : 0l;
        if (exchange) {
          std::swap(left, right);
        }
        if (keep) {
          asm("stc;\n"
          "\tsbbq %2, %0;\n"
          "\tsetc %1;"
          : "=q" (*a_it), "=q" (keep) : "q" (right), "0" (left));
        } else {
          asm("subq %2, %0;\n"
          "\tsetc %1;\n"
          : "=q" (*a_it), "=q" (keep) : "q" (right), "0" (left));
        }
      }
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
