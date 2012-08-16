#ifndef CRYPTO_PRIMETESTER_H
#define CRYPTO_PRIMETESTER_H

#include "longint.h"

namespace Crypto {
  
  class PrimeTester
  {
  public:
    DataStructures::LongInt random_prime(const DataStructures::LongInt& max) const;

    bool is_prime(const DataStructures::LongInt& number) const;

  };
  
}

#endif // CRYPTO_PRIMETESTER_H
