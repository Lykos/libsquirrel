#ifndef DATASTRUCTURES_PREC_MACRO_H
#define DATASTRUCTURES_PREC_MACRO_H

#include "preconditionviolation.h"

#define PREC(type, cond) \
  if (!(cond)) { \
    throw DataStructures::PreconditionViolation(ConditionType::type, #type ": " #cond " is violated."); \
  }

#endif // DATASTRUCTURES_PREC_MACRO_H
