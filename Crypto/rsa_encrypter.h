#ifndef CRYPTO_RSA_ENCRYPTER_H
#define CRYPTO_RSA_ENCRYPTER_H

#include "Crypto_global.h"
#include "rsa_types.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT Encrypter
    {
    private:
      public_key_t m_public_key;

    public:
      inline Encrypter(const public_key_t& public_key): m_public_key (public_key)  {}

      cipher_text_t encrypt(const plain_text_t& plain_text);

    };

  }

}

#endif // CRYPTO_RSA_ENCRYPTER_H
