#include "incdec.h"
#include "assembly.h"

namespace DataStructures {

  namespace LongArithmetic {
    
    inline bool inc(part_type* begin, part_type* const end)
    {
      bool keep = true;
      for (; keep && begin < end; ++begin) {
        ASM_INC_SETCF(*begin, keep);
      }
      return keep;
    }

    inline bool dec(part_type* begin, part_type* const end)
    {
      bool keep = true;
      for (; keep && begin < end; ++begin) {
        arithmetic_assert(begin < end);
        ASM_DEC_SETCF(*begin, keep);
      }
      return keep;
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
