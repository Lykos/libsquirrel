#ifndef DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H
#define DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H

namespace DataStructures {

  class LongInt;

  namespace LongArithmetic {
    
    void divide(LongInt& dividend, LongInt& divisor, LongInt& quotient, LongInt& remainder, bool remainder_needed);

  } // namespace LongArithmetic

} // namespace DataStructures

#endif // DATASTRUCTURES_LONGARITHMETIC_DIVIDE_H
