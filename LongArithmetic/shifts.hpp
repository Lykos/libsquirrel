#include "shifts.h"

namespace LongArithmetic {

  namespace Operations {

    inline part_type shift_left(part_type* begin, part_type* end, size_type offset)
    {
      if (offset == 0) {
        return 0;
      }
      arithmetic_assert(offset < PART_SIZE);
      part_type carry = 0;
      for (; begin < end; ++begin) {
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (*begin << offset) | carry;
        carry = *begin >> (PART_SIZE - offset);
        *begin = shifted;
      }
      return carry;
    }

    inline part_type shift_right(part_type* begin, part_type* end, size_type offset)
    {
      if (offset == 0) {
        return 0;
      }
      arithmetic_assert(offset < PART_SIZE);
      part_type carry = 0;
      for (; end > begin;) {
        --end;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (*end >> offset) | carry;
        carry = *end << (PART_SIZE - offset);
        *end = shifted;
      }
      return carry;
    }
    
  } // namespace LongArithmetic

} // namespace LongArithmetic
