#ifndef CRYPTO_H
#define CRYPTO_H

#include "Crypto_global.h"
#include "longint.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSAKey
  {
  public:
    typedef DataStructures::index_type exponent_t;
    typedef DataStructures::LongInt number_t;
    RSAKey(exponent_t exponent, const number_t& modulus);

  private:
    exponent_t m_exponent;
    number_t m_modulus;
  };

}

#endif // CRYPTO_H
