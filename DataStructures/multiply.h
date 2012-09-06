#ifndef DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
#define DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H

#include "longint.h"

namespace DataStructures {

  namespace LongArithmetic {

    LongInt::part_type* multiply(const LongInt::part_type* a_begin,
                                 const LongInt::part_type* a_end,
                                 const LongInt::part_type* b_begin,
                                 const LongInt::part_type* b_end,
                                 LongInt::part_type* c_begin,
                                 LongInt::part_type* c_end);

    inline LongInt::part_list::iterator multiply(const LongInt::part_list::const_iterator& a_begin,
                                                 const LongInt::part_list::const_iterator& a_end,
                                                 const LongInt::part_list::const_iterator& b_begin,
                                                 const LongInt::part_list::const_iterator& b_end,
                                                 const LongInt::part_list::iterator& c_begin,
                                                 const LongInt::part_list::iterator& c_end)
    {
      LongInt::part_type* end_ptr = multiply(&a_begin[0],
                                             &a_begin[0] + (a_end - a_begin),
                                             &b_begin[0],
                                             &b_begin[0] + (b_end - b_begin),
                                             &c_begin[0],
                                             &c_begin[0] + (c_end - c_begin));
      return c_begin + (end_ptr - &c_begin[0]);
    }

    LongInt::size_type space_usage(LongInt::size_type size_a, LongInt::size_type size_b);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
