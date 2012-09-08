#ifndef DATASTRUCTURES_LONGARITHMETIC_ADD_H
#define DATASTRUCTURES_LONGARITHMETIC_ADD_H

/*
 * Internal header, clients should not include.
 */
namespace DataStructures {

  namespace LongArithmetic {

    void inline add(part_type* a_begin,
                    part_type* a_end,
                    const part_type* b_begin,
                    const part_type* b_end);

  } // namespace LongArithmetic

} // namespace DataStructures

#include "add.hpp"

#endif // DATASTRUCTURES_LONGARITHMETIC_ADD_H
