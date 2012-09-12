#include "preconditionviolation.h"

namespace DataStructures {
  
  PreconditionViolation::PreconditionViolation(DataStructures::ConditionType type, const char* dummy_message):
    m_type (type)
  {
    switch (type) {
    case OutOfRange:
      m_message = "Invalid index.";
      break;
    case EmptyList:
      m_message = "Cannot take front/back for empty lists.";
      break;
    default:
      m_message = dummy_message;
    }
  }
  
} // namespace DataStructures
