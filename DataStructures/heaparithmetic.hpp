#ifndef DATASTRUCTURES_HPPEAP_ARITHMETIC_HPP
#define DATASTRUCTURES_HPPEAP_ARITHMETIC_HPP

#include "heaparithmetic.h"
#include "arithmetichelper.h"

namespace DataStructures {

  namespace HeapArithmetic {

    using namespace ArithmeticHelper;

    inline uint64_t parent(uint64_t index)
    {
      return (index - 1) / 2;
    }

    inline uint64_t left_child(uint64_t index)
    {
      return index * 2 + 1;
    }

    inline uint64_t right_child(uint64_t index)
    {
      return index * 2 + 2;
    }

  }

}

#endif // DATASTRUCTURES_HPPEAP_ARITHMETIC_HPP
