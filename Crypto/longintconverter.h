#ifndef CRYPTO_LONGINTCONVERTER_H
#define CRYPTO_LONGINTCONVERTER_H

#include "Crypto_global.h"
#include "longint.h"

namespace Crypto {
  
  class LongIntConverter
  {
  public:
    typedef u_int8_t byte_t;

    typedef u_int32_t number_size_t;

    DataStructures::LongInt read_number(const u_int8_t* text, number_size_t length) const;

    number_size_t number_length(const DataStructures::LongInt& number) const;

    void write_number(const DataStructures::LongInt& number, u_int8_t* text, number_size_t length) const;
  };
  
} // namespace Crypto

#endif // CRYPTO_LONGINTCONVERTER_H
