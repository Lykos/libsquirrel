#include "divide.h"
#include "longint.h"
#include "platform.h"
#include "assembly.h"
#include "conditiontype.h"
#include "preconditionviolation.h"

namespace DataStructures {

  namespace LongArithmetic {

    static const LongInt ZERO = 0;

    // No aliasing allowed at this stage, all numbers are assumed to be positive
    void divide(LongInt& dividend, LongInt& divisor, LongInt& quotient, LongInt& remainder, bool remainder_needed)
    {
      PREC(DivideByZero, divisor != ZERO);
      if (dividend < divisor) {
        if (remainder_needed) {
          remainder = dividend;
        }
        quotient = ZERO;
        return;
      }
      // Maximal factor we can multiply the divisor with without increasing its size.
      part_type scale_factor = 1;
      part_type divisor_first_digit = divisor.m_content[divisor.size() - 1];
      arithmetic_assert(divisor_first_digit != 0);
      if (divisor_first_digit + 1 != 0) {
        // (1 << 64) / (divisor_last_digit + 1)
        ASM_CALC_SCALE(divisor_first_digit + 1, scale_factor);
      }
      // This scaling does not change the result because it crosses out,
      // but it ensures that the first digit of the divisor is at least 1 << 63.
      if (scale_factor > 1) {
        LongInt scale = scale_factor;
        dividend *= scale;
        divisor *= scale;
      }
      divisor_first_digit = divisor.m_content[divisor.size() - 1];
      arithmetic_assert(divisor_first_digit >= (1ul << 63));
      LongInt::size_type divisor_size = divisor.size();
      // Initialize the results
      quotient = ZERO;
      remainder = ZERO;
      for (LongInt::size_type i = dividend.size(); i > 0;) {
        --i;
        remainder <<= PART_SIZE;
        remainder += dividend.m_content[i];
        if (remainder.size() >= divisor_size) {
          // Guess according to the first one or two parts of the active part and the first digit of the divisor,
          // how many times the divisor fits into the active part. This guess can never be too low and because
          // of our scaling factor, it can be at most 2 to high (according to a proof of Knuth)
          part_type guess;
          ASM_DIVIDE(remainder.m_content[divisor_size - 1], remainder.part_at(divisor_size), divisor_first_digit, guess);
           LongInt back_calculated (divisor * LongInt(guess));
#ifdef ARITHMETIC_DEBUG
          LongInt::size_type old_guess = guess;
#endif
          while (back_calculated > remainder) {
            back_calculated -= divisor;
            --guess;
          }
          arithmetic_assert(old_guess >= guess);
          arithmetic_assert(back_calculated + divisor > remainder);
          arithmetic_assert(old_guess - guess <= 2);
          remainder -= back_calculated;
          quotient.pad_zeros(i + 1);
          quotient.m_content[i] = guess;
        }
      }
      if (remainder_needed) {
        if (scale_factor != 1) {
          // We have to take back the scale_factor
          part_type upper = 0, lower = 0;
          LongInt old_remainder (std::move(remainder));
          remainder = ZERO;
          for (LongInt::size_type i = old_remainder.size(); i > 0;) {
            --i;
            lower = old_remainder.m_content[i];
            remainder.pad_zeros(i + 1);
            // upper:lower / scale_factor, store remainder into upper
            ASM_DIVIDE_REMAINDER(lower, upper, scale_factor, remainder.m_content[i], upper);
          }
          // The division has to work without remainder
          arithmetic_assert(upper == 0);
        }
        remainder.remove_zeros();
      }
      quotient.remove_zeros();
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
