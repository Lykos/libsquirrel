#ifndef DATASTRUCTURES_PRECONDITIONVIOLATION_H
#define DATASTRUCTURES_PRECONDITIONVIOLATION_H
#include "conditiontype.h"
#include <stdexcept>

namespace DataStructures {

  class PreconditionViolation : public std::exception
  {
  public:
    PreconditionViolation(DataStructures::ConditionType type, const char* message);

    DataStructures::ConditionType type() const { return m_type; }

    virtual const char* what() const throw() { return m_message; }

  private:
    DataStructures::ConditionType m_type;

    const char* m_message;

  };

} // namespace DataStructures

#endif // DATASTRUCTURES_PRECONDITIONVIOLATION_H
