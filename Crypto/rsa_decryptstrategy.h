#ifndef CRYPTO_RSA_DECRYPTSTRATEGY_H
#define CRYPTO_RSA_DECRYPTSTRATEGY_H

#include "Crypto/rsa_types.h"

namespace Crypto {

  namespace RSA {

    class DecryptStrategy
    {
    public:
      inline DecryptStrategy(const private_key_t& private_key): m_private_key (private_key) {}

      virtual plain_text_t decrypt(const cipher_text_t& cipher_text) const = 0;

      virtual DecryptStrategy* copy() const = 0;

      virtual ~DecryptStrategy() {}

    protected:
      private_key_t m_private_key;

    };

  }

}

#endif // CRYPTO_RSA_DECRYPTSTRATEGY_H
