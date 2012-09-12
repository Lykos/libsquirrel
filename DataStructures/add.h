#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

/**
 * Internal header file which should not be included by users directly.
 */
namespace DataStructures {

  namespace LongArithmetic {

    /**
     * Interprets two chunks of memory as unsigned long numbers and adds them.
     * The first chunk has to have enough space for the second one to fit in.
     *
     * @brief add Adds two memory chunks as unsigned integers.
     * @param tgt_begin Start of the target chunk
     * @param tgt_end End of the source chunk
     * @param src_begin Start of the target chunk
     * @param src_end End of the source chunk
     */
    void inline add(part_type* tgt_begin,
                    part_type* tgt_end,
                    const part_type* src_begin,
                    const part_type* src_end);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "add.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
