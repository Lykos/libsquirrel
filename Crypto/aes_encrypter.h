#ifndef CRYPTO_AES_ENCRYPTER_H
#define CRYPTO_AES_ENCRYPTER_H

#include "aes_helper.h"
#include "aes_constants.h"
#include "types.h"
#include <string>

namespace Crypto {

  namespace AES {

    class Encrypter
    {
    private:
      std::string m_expanded_key;

      number_size_t m_rounds;

      Helper m_helper;

    public:
      Encrypter(const std::string& key);

      std::string encrypt(const std::string& plain);

      number_size_t plain_block_size() const { return BLOCK_BYTE_SIZE; }

      number_size_t cipher_block_size() const { return BLOCK_BYTE_SIZE; }

    };

  }

}

#endif // CRYPTO_AES_ENCRYPTER_H
