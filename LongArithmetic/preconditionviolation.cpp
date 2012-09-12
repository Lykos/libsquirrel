#include "preconditionviolation.h"

namespace LongArithmetic {
  
  PreconditionViolation::PreconditionViolation(ConditionType type, const char* dummy_message):
    m_type (type)
  {
    switch (type) {
    default:
      m_message = dummy_message;
    }
  }
  
} // namespace LongArithmetic
