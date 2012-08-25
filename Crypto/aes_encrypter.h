#ifndef CRYPTO_AES_ENCRYPTER_H
#define CRYPTO_AES_ENCRYPTER_H

#include "Crypto_global.h"
#include "aes_helper.h"

namespace Crypto {

  namespace AES {

    class CRYPTOSHARED_EXPORT Encrypter
    {
    private:
      char* m_expanded_key;

      uint m_rounds;

      Helper m_helper;

    public:
      explicit Encrypter(const char* key, uint key_length);

      ~Encrypter();

      void encrypt(const char* plain, char* cipher);

    };

  }

}

#endif // CRYPTO_AES_ENCRYPTER_H
