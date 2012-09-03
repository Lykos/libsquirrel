#ifndef CRYPTO_PRECONDITIONVIOLATION_H
#define CRYPTO_PRECONDITIONVIOLATION_H
#include "conditiontype.h"
#include <stdexcept>
#define PREC(type, cond) \
  if (!(cond)) { \
    throw PreconditionViolation(ConditionType::type, #type ": " #cond " is violated."); \
  }

namespace Crypto {
  
  class PreconditionViolation : public std::exception
  {
  public:
    PreconditionViolation(ConditionType type, const char* message) throw();

    ConditionType get_type() const throw() { return m_type; }

    virtual const char* what() const throw() { return m_message; }

  private:
    ConditionType m_type;

    const char* m_message;

  };
  
} // namespace Crypto

#endif // CRYPTO_PRECONDITIONVIOLATION_H
