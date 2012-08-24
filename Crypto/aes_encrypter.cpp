#include "aes_encrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <stdexcept>

namespace Crypto {

  namespace AES {

    Encrypter::Encrypter(const key_t& key): CryptoEncrypter(key)
    {
      KeyExpander expander;
      expander.expand(CryptoEncrypter::m_public_key, m_expanded_key);
    }

    cipher_t Encrypter::encrypt(const plain_t& plain, cipher_t& cipher)
    {
      for (uint i = 0; i < BLOCK_SIZE; ++i) {
        cipher[i] = plain[i];
      }
      uint key_length = m_expanded_key.key_length;
      uint rounds;
      if (key_length == AES_128_BYTES) {
        rounds = AES_128_ROUNDS;
      } else if (key_length == AES_192_BYTES) {
        rounds = AES_192_ROUNDS;
      } else if (key_length == AES_256_BYTES) {
        rounds = AES_256_ROUNDS;
      } else {
        throw std::logic_error("Invalid key size.");
      }
      apply_round_key(cipher, m_expanded_key);
      for (uint i = 1; i < rounds - 1; ++i) {
        sub_bytes();
        apply_round_key(cipher, m_expanded_key + i * 4);
      }
    }

  }

}
