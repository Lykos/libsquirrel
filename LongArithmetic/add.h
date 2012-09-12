#ifndef LONGARITHMETIC_LONGARITHMETIC_ADD_H
#define LONGARITHMETIC_LONGARITHMETIC_ADD_H

#include "platform.h"

/**
 * Internal header file which should not be included by users directly.
 */
namespace LongArithmetic {

  namespace Operations {

    /**
     * Interprets two ranges of memory as unsigned long numbers and adds the
     * source number to the target number.
     *
     * If the source number is larger than the target number, the behaviour is undefined.
     * Note that the source range may be larger than the target range and the
     * result is still valid, if the upper part of the source range only consists
     * of zeroes.
     *
     * Not intended for direct use by clients.
     *
     * @brief add Adds two memory chunks as unsigned integers.
     * @param tgt_begin Pointer the start of the target range
     * @param tgt_end Pointer th the end of the source range
     * @param src_begin Pointer to the start of the target range
     * @param src_end Pointer to the end of the source chunk
     * @return Carry bit after the end of the target range.
     */
    inline void add(part_type* tgt_begin,
                    part_type* tgt_end,
                    const part_type* src_begin,
                    const part_type* src_end);

  } // namespace LongArithmetic

} // namespace LongArithmetic

#include "add.hpp"

#endif // LONGARITHMETIC_LONGARITHMETIC_ADD_H
