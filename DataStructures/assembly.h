#ifndef DATASTRUCTURES_ASSEMBLY_H
#define DATASTRUCTURES_ASSEMBLY_H

#include "platform.h"
#include <stdint.h>
#include <climits>

// Internal header, clients should not include. Appears in header for inlining.
// Contains all the platform dependent code.

#ifdef USE_ASSEMBLY
// Multiplies a, b and stores low bytes in c0, high bytes in c1
#define ASM_MUL(c0, c1, a, b) asm("\tmulq %2;\n" : "=a" (c0), "=d" (c1) : "r" (a), "0" (b) : "cc")

// Adds b0:b1 to a0:a1 with carry
#define ASM_TWO_ADD(a0, a1, b0, b1) \
  asm("\taddq %2, %0;\n" \
      "\tadcq %3, %1;\n" \
      : "=g" (a0), "=g" (a1) : "g" (b0), "g" (b1), "0" (a0), "1" (a1) : "cc")

#define ASM_ADD_SETCF(a, b, carry) \
  asm("\taddq %2, %0;\n" \
      "\tsetc %1;\n" \
       : "=g" (a), "=g" (carry) : "r" (b), "0" (a) : "cc")

#define ASM_ADD_CARRY_SETCF(a, b, carry) \
asm("\tstc;\n" \
    "\tadcq %2, %0;\n" \
    "\tsetc %1;" \
    : "=g" (a), "=g" (carry) : "r" (b), "0" (a) : "cc")

#define ASM_BIT_SCAN(n, offset) \
asm ("\tbsrq %1, %0;\n" \
     : "=r"(result) : "r" (x) : "cc")

#define ASM_SUBTRACT_CARRY_SETCF(a, b, carry) \
asm("\tstc;\n" \
    "\tsbbq %2, %0;\n" \
    "\tsetc %1;\n" \
    : "=g" (a), "=g" (carry) : "g" (b), "0" (a) : "cc")

#define ASM_SUBTRACT_SETCF(a, b, carry) \
asm("\tsubq %2, %0;\n" \
    "\tsetc %1;\n" \
    : "=g" (a), "=g" (carry) : "g" (b), "0" (a) : "cc")

#define ASM_INC_SETCF(a, carry) \
asm("\tincq %0;\n" \
    "\tsetc %1;\n" \
    : "=q" (a), "=q" (carry) : "0" (a), "1" (carry) : "cc")

#define ASM_DEC_SETCF(a, carry) \
asm("\tdecq %0;\n" \
    "\tsetc %1;\n" \
    : "=q" (a), "=q" (carry) : "0" (a), "1" (carry) : "cc")

#define ASM_CALC_SCALE(digit, scale) \
asm("\tmovq $0x1, %%rdx;\n" \
    "\txorq %%rax, %%rax;\n" \
    "\tdiv %1;" \
    : "=a" (scale_factor) : "c" (divisor_first_digit + 1) : "%rdx", "cc")

#define ASM_DIVIDE(dividend0, dividend1, divisor, quotient) \
asm("\tdiv %3;\n" \
    : "=a" (quotient) : "d" (dividend1), "a" (dividend0), "r" (divisor) : "cc")

#define ASM_DIVIDE_REMAINDER(dividend0, dividend1, divisor, quotient, remainder) \
asm("\tdiv %2;\n" \
    : "=a" (quotient), "=d" (remainder) : "r" (divisor), "a" (dividend0), "d" (dividend1) : "cc")
#else
#define HALF_SIZE (sizeof(part_type) * CHAR_BIT / 2)
#define HALF_MASK (1 << HALF_SIZE)

// Multiplies a, b and stores low bytes in c0, high bytes in c1
#define ASM_MUL(c0, c1, a, b)
{ \
  part_type a0 = (a) & HALF_MASK;
  part_type a1 = ((a) >> HALF_SIZE) & HALF_MASK;
  part_type b0 = (b) & HALF_MASK;
  part_type b1 = ((b) >> HALF_SIZE) & HALF_MASK;
  part_type d0 = a0 * b0;
  part_type d1 = a0 * b1 + a1 * b0;
  part_type d2 = a1 * b1;
  (c0) = d0 + (d1 << HALF_SIZE);
  (c1) = d2 + (d1 >> HALF_SIZE) & HALF_MASK;
}

#define ASM_ADD_SETCF(a, b, carry) \
{ \
  part_type c = (a) + (b); \
  (carry) = c < (a); \
  (a) = c; \
}

  // Adds b0:b1 to a0:a1 with carry
#define ASM_TWO_ADD(a0, a1, b0, b1) \
{ \
  part_type c0 = (a0) + (b0); \
  (a1) += (b1) + (c0 < (a0)); \
  (a0) = (c0); \
}

#define ASM_ADD_CARRY_SETCF(a, b, carry) \
{ \
  part_type c = (a) + (b) + (carry); \
  (carry) = c < (a); \
  (a) = c; \
}

#define ASM_BIT_SCAN(n, offset) \
{ \
  offset = 0; \
  for (part_type i = n; i > 0; i >>= 1) { \
    ++offset; \
  } \
}

#define ASM_SUBTRACT_SETCF(a, b, carry) \
{ \
  part_type c = (a) - (b); \
  (carry) = c > (a); \
  (a) = c; \
}

#define ASM_SUBTRACT_CARRY_SETCF(a, b, carry) \
{ \
  part_type c = (a) - (b) - (carry); \
  (carry) = c > (a); \
  (a) = c; \
}

#define ASM_INC_SETCF(a, carry) \
{ \
  part_type c = ++(a); \
  (carry) = c < (a); \
}

#define ASM_DEC_SETCF(a, carry) \
{ \
  part_type c = --(a); \
  (carry) = c > (a); \
}

#define ASM_DIVIDE_REMAINDER(dividend0, dividend1, divisor, quotient, remainder) // TODO

#define ASM_DIVIDE(dividend0, dividend1, divisor, quotient) \
{ \
  part_type remainder; \
  ASM_DIVIDE_REMAINDER(dividend0, dividend1, divisor, quotient, remainder); \
}

#define ASM_CALC_SCALE(digit, scale) \
{ \
  part_type remainder; \
  ASM_DIVIDE(0, 1, digit, scale); \
}
#endif

#endif // DATASTRUCTURES_ASSEMBLY_H
