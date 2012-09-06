#ifndef DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
#define DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H

#include "longint.h"

namespace DataStructures {

  namespace LongArithmetic {
    
    LongInt::part_list::iterator multiply(const LongInt::part_list::const_iterator& a_begin,
                                          const LongInt::part_list::const_iterator& a_end,
                                          const LongInt::part_list::const_iterator& b_begin,
                                          const LongInt::part_list::const_iterator& b_end,
                                          const LongInt::part_list::iterator& c_begin,
                                          const LongInt::part_list::iterator& c_end);


    std::pair<LongInt::part_list::const_iterator, LongInt::part_list::const_iterator> inline calc_xy2(const LongInt::part_list::const_iterator& xy0_begin,
                                                                                                      const LongInt::part_list::const_iterator& xy0_end,
                                                                                                      const LongInt::part_list::const_iterator& xy1_begin,
                                                                                                      const LongInt::part_list::const_iterator& xy1_end,
                                                                                                      LongInt::part_list::iterator& c_begin,
                                                                                                      const LongInt::part_list::iterator& c_end);

    LongInt::size_type space_usage(LongInt::size_type size_a, LongInt::size_type size_b);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
