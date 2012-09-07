#ifndef DATASTRUCTURES_ASSEMBLY_H
#define DATASTRUCTURES_ASSEMBLY_H

#include <stdint.h>

// Internal header, clients should not include. Appears in header for inlining.
// Contains all the platform dependent code needed for the long arithmetic
// ArithmeticHelper may contain platform dependent code, too.

// Multiplies a, b and stores low bytes in c0, high bytes in c1
#define ASM_MUL(c0, c1, a, b) asm("\tmulq %2;\n" : "=a" (c0), "=d" (c1) : "r" (a), "0" (b) : "cc");

// Adds b0:b1 to a0:a1 with carry
#define ASM_TWO_ADD(a0, a1, b0, b1) \
  asm("\taddq %2, %0;\n" \
      "\tadcq %3, %1;\n" \
      : "=g" (a0), "=g" (a1) : "g" (b0), "g" (b1), "0" (a0), "1" (a1) : "cc");

#endif // DATASTRUCTURES_ASSEMBLY_H
