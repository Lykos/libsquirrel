#ifndef DATASTRUCTURES_LONGARITHMETIC_COMPARE_H
#define DATASTRUCTURES_LONGARITHMETIC_COMPARE_H

#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {
    
    inline int_fast8_t compare_to(const part_type* const a_begin,
                                  const part_type* a_end,
                                  const part_type* const b_begin,
                                  const part_type* b_end);
    
  } // namespace LongArithmetic

} // namespace DataStructures

#include "compare.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_COMPARE_H
