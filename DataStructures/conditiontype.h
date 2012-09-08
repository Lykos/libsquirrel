#ifndef CONDITIONTYPE_H
#define CONDITIONTYPE_H

namespace DataStructures {

  enum ConditionType {
    OutOfRange,
    EmptyList,
    NumberLength,
    InvalidIterator,
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

#endif // CONDITIONTYPE_H
