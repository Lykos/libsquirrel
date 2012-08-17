#ifndef CRYPTO_RSA_ENCRYPTER_H
#define CRYPTO_RSA_ENCRYPTER_H

#include "Crypto_global.h"
#include "encrypter.h"
#include "rsa_types.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT Encrypter : public Crypto::Encrypter<public_key_t, plain_text_t, cipher_text_t>
    {
    private:
      typedef Crypto::Encrypter<public_key_t, plain_text_t, cipher_text_t> CryptoEncrypter;

    public:
      inline Encrypter(const public_key_t& public_key): CryptoEncrypter (public_key)  {}

      inline Encrypter(const Encrypter& other): CryptoEncrypter(other) {}

      inline Encrypter& operator=(const Encrypter& other) { CryptoEncrypter::operator=(other); return *this; }

      cipher_text_t encrypt(const plain_text_t& plain_text) const;

    };

  }

}

#endif // CRYPTO_RSA_ENCRYPTER_H
