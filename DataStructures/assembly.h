#ifndef DATASTRUCTURES_ASSEMBLY_H
#define DATASTRUCTURES_ASSEMBLY_H

#include <stdint.h>

// Internal header, clients should not include. Appears in header for inlining.
// Contains all the platform dependent code.

// Multiplies a, b and stores low bytes in c0, high bytes in c1
#define ASM_MUL(c0, c1, a, b) asm("\tmulq %2;\n" : "=a" (c0), "=d" (c1) : "r" (a), "0" (b) : "cc");

// Adds b0:b1 to a0:a1 with carry
#define ASM_TWO_ADD(a0, a1, b0, b1) \
  asm("\taddq %2, %0;\n" \
      "\tadcq %3, %1;\n" \
      : "=g" (a0), "=g" (a1) : "g" (b0), "g" (b1), "0" (a0), "1" (a1) : "cc");

#define ASM_ADD_SETCF(a, b, carry) \
  asm("\taddq %2, %0;\n" \
      "\tsetc %1;\n" \
       : "=g" (a), "=g" (carry) : "r" (b), "0" (a) : "cc");

#define ASM_ADD_CARRY_SETCF(a, b, carry) \
asm("\tstc;\n" \
    "\tadcq %2, %0;\n" \
    "\tsetc %1;" \
    : "=g" (a), "=g" (carry) : "r" (b), "0" (a) : "cc");

#define ASM_BIT_SCAN(n, offset) \
asm ("\tbsrq %1, %0;\n" \
     : "=r"(result) : "r" (x) : "cc");

#define ASM_SUBTRACT_CARRY_SETCF(a, b, carry) \
asm("\tstc;\n" \
    "\tsbbq %2, %0;\n" \
    "\tsetc %1;\n" \
    : "=g" (a), "=g" (carry) : "g" (b), "0" (a) : "cc");

#define ASM_SUBTRACT_SETCF(a, b, carry) \
asm("\tsubq %2, %0;\n" \
    "\tsetc %1;\n" \
    : "=g" (a), "=g" (carry) : "g" (b), "0" (a) : "cc");

#define ASM_INC_SETCF(a, carry) \
asm("\tincq %0;\n" \
    "\tsetc %1;\n" \
    : "=q" (a), "=q" (carry) : "0" (a), "1" (carry) : "cc");

#define ASM_CALC_SCALE(digit, scale) \
asm("\tmovq $0x1, %%rdx;\n" \
    "\txorq %%rax, %%rax;\n" \
    "\tdiv %1;" \
    : "=a" (scale_factor) : "c" (divisor_first_digit + 1) : "%rdx", "cc");

#define ASM_DIVIDE(dividend0, dividend1, divisor, quotient) \
asm("\tdiv %3;\n" \
    : "=a" (quotient) : "d" (dividend1), "a" (dividend0), "r" (divisor) : "cc");

#define ASM_DIVIDE_REMAINDER(dividend0, dividend1, divisor, quotient, remainder) \
asm("\tdiv %2;\n" \
    : "=a" (quotient), "=d" (remainder) : "r" (divisor), "a" (dividend0), "d" (dividend1) : "cc");

#endif // DATASTRUCTURES_ASSEMBLY_H
