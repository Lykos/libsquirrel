#include "incdec.h"
#include "assembly.h"

namespace DataStructures {

  namespace LongArithmetic {
    
    inline bool inc(part_type* begin, part_type* const end)
    {
      bool carry = true;
      for (; carry && begin < end; ++begin) {
        ASM_INC_SETCF(*begin, carry);
      }
      return carry;
    }

    inline void dec(part_type* begin, part_type* const end)
    {
      bool carry = true;
      for (; carry && begin < end; ++begin) {
        arithmetic_assert(begin < end);
        ASM_DEC_SETCF(*begin, carry);
      }
      arithmetic_assert(!carry);
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
