#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <climits>
#include <cassert>
#include <cstring>
#include <stdexcept>

namespace Crypto {

  namespace AES {

    inline void KeyExpander::schedule_core(char* in, uint i)
    {
      m_helper.sub_word(m_helper.rotate_word(in)) ^ Rcon[i];
    }

    void KeyExpander::expand(char* key, uint key_length) const
    {
      uint rounds;
      if (key_length == AES_128_BYTES) {
        rounds = AES_128_ROUNDS;
      } else if (key_length == AES_192_BYTES) {
        rounds = AES_192_ROUNDS;
      } else if (key_length == AES_256_BYTES) {
        rounds = AES_256_ROUNDS;
      } else {
        throw std::logic_error("Invalid key length.");
      }
      uint j = 0;
      for (; j < key_length; ++j) {
        result.bytes[j] = key.bytes[j];
      }
      for (uint j = key_length; j < (rounds + 1) * BLOCK_BYTE_SIZE;)
      {
        char_t t[4];
        for (uint k = 0; k < BLOCK_ROWS; ++k) {
          t[k] = key[j - BLOCK_ROWS + k];
        }
        schedule_core(t, i);
        ++i;
        for (uint k = 0; k < 16; ++k) {
          result.bytes[j + k] = t[k % 4] ^ result.bytes[j];
        }
      }
    }

  } // namespace AES

} // namespace Crypto
