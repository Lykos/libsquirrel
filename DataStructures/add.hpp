#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP
#define DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP

#include "incdec.h"
#include "add.h"
#include "assembly.h"
#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {

    inline void add(part_type* tgt_begin,
                    part_type* tgt_end,
                    const part_type* src_begin,
                    const part_type* src_end)
    {
      bool keep = false;
      while (src_begin < src_end && tgt_begin < tgt_end) {
        if (keep) {
          ASM_ADD_CARRY_SETCF(*tgt_begin, *src_begin, keep);
        } else {
          ASM_ADD_SETCF(*tgt_begin, *src_begin, keep);
        }
        ++tgt_begin;
        ++src_begin;
      }
      if (keep) {
        arithmetic_assert_nocarry(inc(tgt_begin, tgt_end));
      }
    }

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_HPPPP
