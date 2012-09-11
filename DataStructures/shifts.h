#ifndef DATASTRUCTURES_LONGARITHMETIC_SHIFTS_H
#define DATASTRUCTURES_LONGARITHMETIC_SHIFTS_H

#include "platform.h"

namespace DataStructures {

  namespace LongArithmetic {
    
    /**
     * @brief shift_left does a left shift with a memory chunk interpreted as a number.
     * @param begin Start of the memory chunk
     * @param end End of the memory chunk
     * @param offset Shift offset, may not be larger than the bits in part_type
     * @return The part that falls off.
     */
    inline part_type shift_left(part_type* begin, part_type* end, size_type offset);

    /**
     * @brief shift_left does a right shift with a memory chunk interpreted as a number.
     * @param begin Start of the memory chunk
     * @param end End of the memory chunk
     * @param offset Shift offset, may not be larger than the bits in part_type
     * @return The part that falls off.
     */
    inline part_type shift_right(part_type* begin, part_type* end, size_type offset);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "shifts.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_SHIFTS_H
