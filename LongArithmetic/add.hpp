#ifndef LONGARITHMETIC_LONGARITHMETIC_ADD_HPPPP
#define LONGARITHMETIC_LONGARITHMETIC_ADD_HPPPP

#include "incdec.h"
#include "add.h"
#include "assembly.h"
#include "platform.h"

namespace LongArithmetic {

  namespace Operations {

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

} // namespace LongArithmetic

#endif // LONGARITHMETIC_LONGARITHMETIC_ADD_HPPPP
