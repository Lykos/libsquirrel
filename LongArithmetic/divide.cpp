#include "divide.h"
#include "longint.h"
#include "platform.h"
#include "assembly.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include "arithmetichelper.h"
#include "debug.h"
#include "multiply.h"
#include "shifts.h"

namespace LongArithmetic {

  namespace Operations {

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
      part_type divisor_first_digit = divisor.m_content[divisor.size() - 1];
      arithmetic_assert(divisor_first_digit > 0);
      size_type scale_shift = PART_SIZE - 1 - ArithmeticHelper::log2(divisor_first_digit);
      arithmetic_assert_nocarry(shift_left(&divisor.m_content[0], &divisor.m_content[0] + divisor.size(), scale_shift));
      part_type carry = shift_left(&dividend.m_content[0], &dividend.m_content[0] + dividend.size(), scale_shift);
      if (carry > 0) {
        dividend.m_content.push_back(carry);
      }
      divisor_first_digit = divisor.m_content[divisor.size() - 1];
      arithmetic_assert(divisor_first_digit >= (1ul << 63));
      LongInt::size_type divisor_size = divisor.size();
      const part_type* divisor_begin = divisor.m_content.data();
      const part_type* divisor_end = divisor.m_content.data() + divisor.size();
      size_type space_needed = space_usage(divisor.size(), 1);
      part_type* space_begin = static_cast<part_type*>(malloc(space_needed * sizeof(part_type)));
      part_type* space_end = space_begin + space_needed;
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
          // of our scaling, it can be at most 2 to high (according to a proof of Knuth)
          part_type guess;
          ASM_DIVIDE(remainder.m_content[divisor_size - 1], remainder.part_at(divisor_size), divisor_first_digit, guess);
          part_type* result_end = multiply(divisor_begin, divisor_end, &guess, &guess + 1, space_begin, space_end);
          LongInt back_calculated;
          back_calculated.m_content = LongInt::part_list(space_begin, result_end);
          if (back_calculated.m_content.empty()) {
            back_calculated.m_content.push_back(0);
          }
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
      free(space_begin);
      if (remainder_needed) {
        arithmetic_assert_nocarry(shift_right(&remainder.m_content[0], &remainder.m_content[0] + remainder.size(), scale_shift));
        remainder.remove_zeros();
      }
      quotient.remove_zeros();
    }
    
  } // namespace LongArithmetic

} // namespace LongArithmetic
