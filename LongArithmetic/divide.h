#ifndef LONGARITHMETIC_DIVIDE_H
#define LONGARITHMETIC_DIVIDE_H

namespace LongArithmetic {

  class LongInt;

  namespace Operations {
    
    void divide(LongArithmetic::LongInt& dividend,
                LongArithmetic::LongInt& divisor,
                LongArithmetic::LongInt& quotient,
                LongArithmetic::LongInt& remainder,
                bool remainder_needed);

  } // namespace LongArithmetic

} // namespace LongArithmetic

#endif // LONGARITHMETIC_DIVIDE_H
