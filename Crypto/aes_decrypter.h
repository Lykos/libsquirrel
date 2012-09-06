#ifndef CRYPTO_AES_DECRYPTER_H
#define CRYPTO_AES_DECRYPTER_H

#include "aes_helper.h"
#include "aes_constants.h"
#include "types.h"
#include <string>

namespace Crypto {

  namespace AES {
    
    class Decrypter
    {
    private:

      std::string m_expanded_key;

      number_size_t m_rounds;

      Helper m_helper;

    public:
      Decrypter(const std::string& key);

      std::string decrypt(const std::string& cipher);

      number_size_t cipher_block_size() const { return BLOCK_BYTE_SIZE; }

      number_size_t plain_block_size() const { return BLOCK_BYTE_SIZE; }

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_DECRYPTER_H
