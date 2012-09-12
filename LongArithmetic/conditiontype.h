#ifndef LONG_ARITHMETIC_CONDITIONTYPE_H
#define LONG_ARITHMETIC_CONDITIONTYPE_H

namespace LongArithmetic {

  enum ConditionType {
    NumberLength,
    InvalidInputIterator,
    InvalidRange,
    NotRelativelyPrime,
    DivideByZero,
    DifferentFields,
    NoDigits,
    InvalidDigit,
    NotImplemented,
    InvalidModulus,
    NANConversion,
    InfinityConversion,
    NegativeExponent,
    NegationOverflow,
    NoField
  };

}

#endif // LONG_ARITHMETIC_CONDITIONTYPE_H
