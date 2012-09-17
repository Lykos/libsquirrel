#ifndef LONGARITHMETIC_LONGARITHMETIC_SHIFTS_H
#define LONGARITHMETIC_LONGARITHMETIC_SHIFTS_H

#include "platform.h"

namespace LongArithmetic {

  namespace Operations {
    
    /**
     * This interprets a memory chunk as a number and shifts every part by the given
     * offset and performs the carrying. At the end, it returns the carryover from the
     * leftmost part. Note that it does not handle two complement sign tricks and cannot
     * handle an offset larger than the size of a part. This is an internal function and
     * should not be used by clients.
     *
     * @brief shift_left does a left shift with a memory chunk interpreted as a number.
     * @param begin Start of the memory chunk
     * @param end End of the memory chunk
     * @param offset Shift offset, may not be larger than the bits in part_type
     * @return The part that falls off.
     */
    inline part_type shift_left(part_type* begin, part_type* end, size_type offset);

    /**
     * This interprets a memory chunk as a number and shifts every part by the given
     * offset and performs the carrying. At the end, it returns the carryover from the
     * leftmost part. Note that it does not handle two complement sign tricks and cannot
     * handle an offset larger than the size of a part. This is an internal function and
     * should not be used by clients.
     *
     * @brief shift_left does a right shift with a memory chunk interpreted as a number.
     * @param begin Start of the memory chunk
     * @param end End of the memory chunk
     * @param offset Shift offset, may not be larger than the bits in part_type
     * @return The part that falls off.
     */
    inline part_type shift_right(part_type* begin, part_type* end, size_type offset);

  } // namespace LongArithmetic

} // namespace LongArithmetic

#include "shifts.hpp"

#endif // LONGARITHMETIC_LONGARITHMETIC_SHIFTS_H
