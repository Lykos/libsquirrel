#ifndef CRYPTO_AES_DECRYPTER_H
#define CRYPTO_AES_DECRYPTER_H

#include "Crypto_global.h"
#include "aes_helper.h"

namespace Crypto {

  namespace AES {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    private:
      char* m_expanded_key;

      uint m_rounds;

      Helper m_helper;

    public:
      explicit Decrypter(const char* key, uint key_length);

      ~Decrypter();

      void decrypt(const char* cipher, char* plain);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_DECRYPTER_H
