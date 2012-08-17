#ifndef CRYPTO_PRIMETESTER_H
#define CRYPTO_PRIMETESTER_H

#include "longint.h"
#include "arraylist.h"

namespace Crypto {
  
  class PrimeTester
  {
  public:
    typedef DataStructures::ArrayList<DataStructures::LongInt> factorization_t;

    DataStructures::LongInt random_prime(DataStructures::index_type number_bits) const;

    bool is_prime(const DataStructures::LongInt& number) const;

  };
  
}

#endif // CRYPTO_PRIMETESTER_H
