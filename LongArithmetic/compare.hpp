#include "compare.h"
#include "longint.h"

namespace LongArithmetic {

  namespace Operations {

    typedef LongInt::size_type size_type;
    
    // Compare numbers TODO: Merge the code with the normal compare
    inline int_fast8_t compare_to(const part_type* a_begin,
                                  const part_type* a_end,
                                  const part_type* b_begin,
                                  const part_type* b_end)
    {
      arithmetic_assert(a_begin <= a_end);
      arithmetic_assert(b_begin <= b_end);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      while (b_size < a_size) {
        --a_size;
        --a_end;
        if (*a_end != 0) {
          return 1;
        }
      }
      while (a_size < b_size) {
        --b_size;
        --b_end;
        if (*b_end != 0) {
          return -1;
        }
      }
      for (; a_end > a_begin;) {
        arithmetic_assert(b_end > b_begin);
        --a_end;
        --b_end;
        if (*a_end < *b_end) {
          return -1;
        } else if (*a_end > *b_end) {
          return 1;
        }
      }
      return 0;
    }
    
  } // namespace LongArithmetic

} // namespace LongArithmetic
