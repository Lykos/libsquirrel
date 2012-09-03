#ifndef CRYPTO_AES_ENCRYPTER_H
#define CRYPTO_AES_ENCRYPTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/aes_helper.h"
#include "Crypto/aes_constants.h"
#include "Crypto/types.h"

namespace Crypto {

  namespace AES {

    class CRYPTOSHARED_EXPORT Encrypter
    {
    private:
      uint m_expanded_key_length;

      byte_t* m_expanded_key;

      uint m_rounds;

      Helper m_helper;

    public:
      Encrypter(const byte_t* key, uint key_length);

      Encrypter(const Encrypter& other);

      Encrypter(Encrypter&& other);

      Encrypter& operator=(const Encrypter& other);

      Encrypter& operator=(Encrypter&& other);

      ~Encrypter();

      void encrypt(const byte_t* plain, byte_t* cipher);

      uint plain_block_size() const { return BLOCK_BYTE_SIZE; }

      uint cipher_block_size() const { return BLOCK_BYTE_SIZE; }

    };

  }

}

#endif // CRYPTO_AES_ENCRYPTER_H
