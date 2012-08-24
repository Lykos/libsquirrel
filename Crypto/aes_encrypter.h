#ifndef CRYPTO_AES_ENCRYPTER_H
#define CRYPTO_AES_ENCRYPTER_H

#include "Crypto_global.h"
#include "aes_types.h"
#include "encrypter.h"

namespace Crypto {

  namespace AES {

    class CRYPTOSHARED_EXPORT Encrypter : public Crypto::Encrypter<key_t, plain_t, cipher_t>
    {
    private:
      typedef Crypto::Encrypter<key_t, plain_t, cipher_t> CryptoEncrypter;

    public:
      explicit Encrypter(const key_t& key);


    };

  }

}

#endif // CRYPTO_AES_ENCRYPTER_H
