#ifndef LONGARITHMETIC_PRECONDITIONVIOLATION_H
#define LONGARITHMETIC_PRECONDITIONVIOLATION_H

#include "conditiontype.h"
#include <stdexcept>

namespace LongArithmetic {

  class PreconditionViolation : public std::exception
  {
  public:
    PreconditionViolation(ConditionType type, const char* message);

    ConditionType type() const { return m_type; }

    virtual const char* what() const throw() { return m_message; }

  private:
    ConditionType m_type;

    const char* m_message;

  };

} // namespace LongArithmetic

#endif // LONGARITHMETIC_PRECONDITIONVIOLATION_H
