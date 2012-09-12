#include "shifts.h"

namespace LongArithmetic {

  namespace Operations {

    inline part_type shift_left(part_type* begin, part_type* end, size_type offset)
    {
      arithmetic_assert(offset < PART_SIZE);
      part_type keep = 0;
      for (; begin < end; ++begin) {
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (*begin << offset) | keep;
        keep = *begin >> (PART_SIZE - offset);
        *begin = shifted;
      }
      return keep;
    }

    inline part_type shift_right(part_type* begin, part_type* end, size_type offset)
    {
      arithmetic_assert(offset < PART_SIZE);
      part_type keep = 0;
      for (; end > begin;) {
        --end;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (*end >> offset) | keep;
        keep = *end << (PART_SIZE - offset);
        *end = shifted;
      }
      return keep;
    }
    
  } // namespace LongArithmetic

} // namespace LongArithmetic
