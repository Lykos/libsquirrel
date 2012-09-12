#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP
#define DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP

#include "add.h"
#include "assembly.h"
#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {

    void inline add(part_type* tgt_begin,
                    part_type* tgt_end,
                    const part_type* src_begin,
                    const part_type* src_end)
    {
      for (bool keep = false; keep || src_begin < src_end; ++tgt_begin, ++src_begin) {
        arithmetic_assert(tgt_begin < tgt_end);
        part_type b_part = (src_begin < src_end ? *src_begin : 0);
        if (keep) {
          ASM_ADD_CARRY_SETCF(*tgt_begin, b_part, keep);
        } else {
          ASM_ADD_SETCF(*tgt_begin, b_part, keep);
        }
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP
