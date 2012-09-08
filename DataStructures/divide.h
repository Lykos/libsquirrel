#ifndef DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H
#define DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H

namespace DataStructures {

  class LongInt;

  namespace LongArithmetic {
    
    void divide(DataStructures::LongInt& dividend,
                DataStructures::LongInt& divisor,
                DataStructures::LongInt& quotient,
                DataStructures::LongInt& remainder,
                bool remainder_needed);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H
