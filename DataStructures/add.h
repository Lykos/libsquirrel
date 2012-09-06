#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

// Internal header, clients should not include. Appears in header for inlining.
namespace DataStructures {

  namespace LongArithmetic {

    void inline add(const LongInt::part_list::iterator& a_begin,
                    const LongInt::part_list::iterator& a_end,
                    const LongInt::part_list::const_iterator& b_begin,
                    const LongInt::part_list::const_iterator& b_end)
    {
      bool keep = 0;
      LongInt::part_list::iterator a_it (a_begin);
      LongInt::part_list::const_iterator b_it (b_begin);
      for (; keep == 1 || b_it < b_end; ++a_it, ++b_it) {
        if (a_it >= a_end)
        assert(a_it < a_end);
        LongInt::part_type b_part = b_it < b_end ? *b_it : 0;
        if (keep) {
          asm("stc;\n"
          "\tadcq %2, %0;\n"
          "\tsetc %1;"
          : "=q" (*a_it), "=q" (keep) : "q" (b_part), "0" (*a_it));
        } else {
          asm("addq %2, %0;\n"
          "\tsetc %1;\n"
          : "=q" (*a_it), "=q" (keep) : "q" (b_part), "0" (*a_it));
        }
      }
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
