#ifndef LONGARITHMETIC_DEBUG_H
#define LONGARITHMETIC_DEBUG_H

/**
 * Assertions for internal consistency checks.
 * May be very inefficient and hence they are usually disabled, but
 * they can be turned on to help to track down bugs faster.
 */
#ifdef ARITHMETIC_DEBUG
#define arithmetic_assert(b) assert(b)
#define arithmetic_assert_nocarry(f) { bool carry = f; assert(!carry); }
#else
#define arithmetic_assert(b)
#define arithmetic_assert_nocarry(f) f
#endif

#ifdef ARITHMETIC_DEBUG
#include <iostream>
#include <gmpxx.h>
using namespace std;

namespace LongArithmetic {

    inline void printit(const char* name, bool positive, const part_type* begin, const part_type* end)
    {
      cout << name << " " << (positive ? "" : "-");
      while (end > begin) {
        --end;
        cout << *end << " ";
      }
      cout << endl;
    }

    inline mpz_class to_mpz(const part_type* begin, const part_type* end)
    {
      mpz_class mpz (0);
      while (end > begin) {
        --end;
        mpz <<= PART_SIZE;
        mpz += *end;
      }
      return mpz;
    }

}
#endif

#endif // LONGARITHMETIC_DEBUG_H
