#ifndef CRYPTO_AES_ENCRYPTER_H
#define CRYPTO_AES_ENCRYPTER_H

#include "Crypto_global.h"
#include "aes_types.h"

namespace Crypto {

  namespace AES {

    class CRYPTOSHARED_EXPORT Encrypter
    {
    private:
      typedef Crypto::Encrypter<key_t, plain_t, cipher_t> CryptoEncrypter;

      ex_key_t m_expanded_key;

      Helper m_aes_helper;

    public:
      explicit Encrypter(const key_t& key);

      void encrypt(const plain_t &plain, cipher_t cipher);

    };

  }

}

#endif // CRYPTO_AES_ENCRYPTER_H
