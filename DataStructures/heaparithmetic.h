#ifndef DATASTRUCTURES_HEAP_ARITHMETIC_H
#define DATASTRUCTURES_HEAP_ARITHMETIC_H

#include "arithmetichelper.h"

namespace DataStructures {

  namespace HeapArithmetic {

    inline uint64_t level_base(uint64_t index)
    {
      return next_pow2(index) - 1;
    }

    inline uint64_t parent(uint64_t index)
    {
      uint64_t child_base = level_base(index);
      uint64_t child_offset = index - child_base;
      uint64_t parent_base = child_base >> 1;
      uint64_t parent_offset = child_offset / 2;
      return parent_base + parent_offset;
    }

    inline uint64_t left_child(uint64_t index)
    {
      uint64_t parent_base = level_base(index);
      uint64_t parent_offset = index - parent_base;
      uint64_t child_base = (parent_base << 1) + 1;
      uint64_t child_offset = parent_offset * 2;
      return child_base + child_offset;
    }

    inline uint64_t right_child(uint64_t index)
    {
      return left_child(index) + 1;
    }

  }

}

#endif // DATASTRUCTURES_HEAP_ARITHMETIC_H
