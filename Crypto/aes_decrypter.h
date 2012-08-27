#ifndef CRYPTO_AES_DECRYPTER_H
#define CRYPTO_AES_DECRYPTER_H

#include "Crypto_global.h"
#include "aes_helper.h"
#include "aes_constants.h"
#include "aes_types.h"

namespace Crypto {

  namespace AES {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    private:
      uint m_expanded_key_length;

      aes_byte_t* m_expanded_key;

      uint m_rounds;

      Helper m_helper;

    public:
      Decrypter(const aes_byte_t* key, uint key_length);

      Decrypter(const Decrypter& other);

      Decrypter(Decrypter&& other);

      Decrypter& operator=(const Decrypter& other);

      Decrypter& operator=(Decrypter&& other);

      ~Decrypter();

      void decrypt(const aes_byte_t* cipher, aes_byte_t* plain);

      uint cipher_block_size() const { return BLOCK_BYTE_SIZE; }

      uint plain_block_size() const { return BLOCK_BYTE_SIZE; }

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_DECRYPTER_H
