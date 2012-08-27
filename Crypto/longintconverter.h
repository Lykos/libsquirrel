#ifndef CRYPTO_LONGINTCONVERTER_H
#define CRYPTO_LONGINTCONVERTER_H

#include "Crypto_global.h"
#include "longint.h"

namespace Crypto {
  
  class LongIntConverter
  {
  public:
    typedef u_int8_t byte_t;

    DataStructures::LongInt convert(const u_int8_t* text, uint length);

    void convert(const DataStructures::LongInt& number, u_int8_t* text, uint length);
  };
  
} // namespace Crypto

#endif // CRYPTO_LONGINTCONVERTER_H
