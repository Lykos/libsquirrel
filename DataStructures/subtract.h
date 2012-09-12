#ifndef DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
#define DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H

#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {

    /**
     * Interprets two ranges of memory as unsigned long numbers and subtracts the
     * source number from the target number. If exchange is true, then the target
     * is instead subtracted from the source, but the result is still stored in
     * the target range, so this is NOT equivalent to changing the argument order.
     * If the source number is larger than the target number, the result is invalid.
     *
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
     * @param exchange If true the numbers are exchanged before the subtraction
     */
    inline void subtract(part_type* tgt_begin,
                         part_type* const tgt_end,
                         const part_type* src_begin,
                         const part_type* const src_end,
                         bool exchange);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "subtract.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_SUBTRACT_H
