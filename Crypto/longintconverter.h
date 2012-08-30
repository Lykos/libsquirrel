#ifndef CRYPTO_LONGINTCONVERTER_H
#define CRYPTO_LONGINTCONVERTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/preconditionviolation.h"
#include "DataStructures/longint.h"

namespace Crypto {
  
  class LongIntConverter
  {
  public:
    typedef u_int8_t byte_t;

    typedef u_int32_t number_size_t;

    // Bytes that fit into this number
    static number_size_t fitting_length(const DataStructures::LongInt& number);

    // Bytes required to store this number
    static number_size_t required_length(const DataStructures::LongInt& number);

    DataStructures::LongInt read_number(const u_int8_t* text, number_size_t length) const;

    void write_number(const DataStructures::LongInt& number, u_int8_t* text, number_size_t length) const throw(PreconditionViolation);
  };
  
} // namespace Crypto

#endif // CRYPTO_LONGINTCONVERTER_H