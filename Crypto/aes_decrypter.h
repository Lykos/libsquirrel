#ifndef CRYPTO_AES_DECRYPTER_H
#define CRYPTO_AES_DECRYPTER_H

#include "Crypto_global.h"
#include "aes_helper.h"
#include "aes_constants.h"
#include "types.h"
#include <string>

namespace Crypto {

  namespace AES {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    private:

      std::string m_expanded_key;

      uint m_rounds;

      Helper m_helper;

    public:
      Decrypter(const std::string& key);

      std::string decrypt(const std::string& cipher);

      uint cipher_block_size() const { return BLOCK_BYTE_SIZE; }

      uint plain_block_size() const { return BLOCK_BYTE_SIZE; }

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_DECRYPTER_H
