#ifndef DATASTRUCTURES_PRECONDITIONVIOLATION_H
#define DATASTRUCTURES_PRECONDITIONVIOLATION_H
#include "conditiontype.h"
#include <stdexcept>
#define PREC(type, cond) \
  if (!(cond)) { \
    throw PreconditionViolation(ConditionType::type, #type ": " #cond " is violated."); \
  }

namespace DataStructures {

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

} // namespace DataStructures

#endif // DATASTRUCTURES_PRECONDITIONVIOLATION_H
