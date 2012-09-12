#ifndef DATASTRUCTURES_LONGARITHMETIC_INCDEC_H
#define DATASTRUCTURES_LONGARITHMETIC_INCDEC_H

namespace DataStructures {

  namespace LongArithmetic {

    /**
     * Interprets a memory chunk as a number and increments it by one. This
     * is not intended for direct use by clients.
     *
     * @brief inc Increments a number
     * @param begin Pointer to the start of a number
     * @param end Pointer to the end of a number.
     * @return Carry bit after end
     */
    inline bool inc(part_type* begin, part_type* const end);

    /**
     * Interprets a memory chunk as a number and decrements it by one. This
     * is not intended for direct use by clients. Is not allowed to overflow.
     *
     * @brief inc Decrements a number
     * @param begin Pointer to the start of a number
     * @param end Pointer to the end of a number.
     */
    inline void dec(part_type* begin, part_type* const end);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "incdec.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_INCDEC_H
