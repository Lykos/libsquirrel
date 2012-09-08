#ifndef DATASTRUCTURES_HEAP_ARITHMETIC_H
#define DATASTRUCTURES_HEAP_ARITHMETIC_H

namespace DataStructures {

  namespace HeapArithmetic {

    using namespace ArithmeticHelper;

    inline uint64_t parent(uint64_t index);

    inline uint64_t left_child(uint64_t index);

    inline uint64_t right_child(uint64_t index);

  }

}

#include "heaparithmetic.hpp"

#endif // DATASTRUCTURES_HEAP_ARITHMETIC_H
