#ifndef LONGARITHMETIC_LONGARITHMETIC_COMPARE_H
#define LONGARITHMETIC_LONGARITHMETIC_COMPARE_H

#include "platform.h"

namespace LongArithmetic {

  namespace Operations {
    
    inline int_fast8_t compare_to(const part_type* const a_begin,
                                  const part_type* a_end,
                                  const part_type* const b_begin,
                                  const part_type* b_end);
    
  } // namespace LongArithmetic

} // namespace LongArithmetic

#include "compare.hpp"

#endif // LONGARITHMETIC_LONGARITHMETIC_COMPARE_H
