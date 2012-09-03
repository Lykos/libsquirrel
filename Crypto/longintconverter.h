#ifndef CRYPTO_LONGINTCONVERTER_H
#define CRYPTO_LONGINTCONVERTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/types.h"
#include "DataStructures/longint.h"

namespace Crypto {
  
  class LongIntConverter
  {
  public:
    // Bytes that fit into this number
    static number_size_t fitting_length(const DataStructures::LongInt& number);

    // Bytes required to store this number
    static number_size_t required_length(const DataStructures::LongInt& number);

    DataStructures::LongInt read_number(const std::string& text) const;

    std::string write_number(const DataStructures::LongInt& number, number_size_t length) const throw(PreconditionViolation);
  };
  
} // namespace Crypto

#endif // CRYPTO_LONGINTCONVERTER_H
