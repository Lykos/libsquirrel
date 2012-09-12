#ifndef DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
#define DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H

#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {

    part_type* simple_multiply(const part_type a,
                                        const part_type b,
                                        part_type* c);

    part_type* multiply(const part_type* a_begin,
                                 const part_type* a_end,
                                 const part_type* b_begin,
                                 const part_type* b_end,
                                 part_type* c_begin,
                                 part_type* c_end);

    size_type space_usage(size_type size_a, size_type size_b);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_MULTIPLY_H
