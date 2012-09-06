#ifndef DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
#define DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H

#include "longint.h"

namespace DataStructures {

  namespace LongArithmetic {

    LongInt::part_type* simple_multiply(const LongInt::part_type a,
                                        const LongInt::part_type b,
                                        LongInt::part_type* c);

    LongInt::part_type* multiply(const LongInt::part_type* a_begin,
                                 const LongInt::part_type* a_end,
                                 const LongInt::part_type* b_begin,
                                 const LongInt::part_type* b_end,
                                 LongInt::part_type* c_begin,
                                 LongInt::part_type* c_end);

    LongInt::size_type space_usage(LongInt::size_type size_a, LongInt::size_type size_b);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
