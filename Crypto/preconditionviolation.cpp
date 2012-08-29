#include "preconditionviolation.h"

namespace Crypto {
  
  PreconditionViolation::PreconditionViolation(ConditionType type, const char* message) throw():
    m_type (type),
    m_message (message)
  {
  }
  
} // namespace Crypto
