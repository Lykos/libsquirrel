#ifndef CRYPTO_H
#define CRYPTO_H

#include "Crypto_global.h"
#include "longint.h"
#include "key.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSAKey : public Key
  {
  public:
    typedef DataStructures::index_type exponent_t;
    RSAKey(exponent_t exponent, const text_t& modulus);

    inline exponent_t get_exponent() const
    {
      return m_exponent;
    }

    inline const text_t& get_modulus() const
    {
      return m_modulus;
    }

  private:
    exponent_t m_exponent;
    text_t m_modulus;
  };

}

#endif // CRYPTO_H
