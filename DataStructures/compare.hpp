#include "compare.h"
#include "longint.h"

namespace DataStructures {

  namespace LongArithmetic {

    typedef LongInt::size_type size_type;
    
    // Compare numbers TODO: Merge the code with the normal compare
    inline int_fast8_t compare_to(const part_type* const a_begin,
                                  const part_type* a_end,
                                  const part_type* const b_begin,
                                  const part_type* b_end)
    {
      arithmetic_assert(a_begin <= a_end);
      arithmetic_assert(b_begin <= b_end);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      if (a_size < b_size) {
        return -1;
      } else if (b_size < a_size) {
        return 1;
      }
      for (; a_end > a_begin;) {
        --a_end;
        arithmetic_assert(b_end > b_begin);
        if (*a_begin > *b_begin) {
          return 1;
        } else if (*b_begin > *a_begin) {
          return -1;
        }
      }
      return 0;
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
