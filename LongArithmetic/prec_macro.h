#ifndef LONGARITHMETIC_PREC_MACRO_H
#define LONGARITHMETIC_PREC_MACRO_H

#include "preconditionviolation.h"
#undef PREC
#define PREC(type, cond) \
  if (!(cond)) { \
    throw PreconditionViolation(ConditionType::type, #type ": " #cond " is violated."); \
  }

#endif // LONGARITHMETIC_PREC_MACRO_H
