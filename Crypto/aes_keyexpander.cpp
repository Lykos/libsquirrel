#include "aes_keyexpander.h"
#include "aes_constants.h"
#include "aes_types.h"
#include <climits>
#include <cassert>
#include <cstring>
#include <stdexcept>

namespace Crypto {

  namespace AES {

    KeyExpander::KeyExpander(uint key_length):
      m_key_length (key_length)
    {
      if (key_length == AES_128_BYTES) {
        m_rounds = AES_128_ROUNDS;
      } else if (key_length == AES_192_BYTES) {
        m_rounds = AES_192_ROUNDS;
      } else if (key_length == AES_256_BYTES) {
        m_rounds = AES_256_ROUNDS;
      } else {
        throw std::logic_error("Invalid key length.");
      }
      m_expanded_length = (m_rounds + 1) * BLOCK_BYTE_SIZE;
    }

    inline void KeyExpander::schedule_core(aes_byte_t* in, uint i)
    {
      m_helper.rotate_word(in);
      m_helper.sub_word(in);
      in[0] ^= Rcon[i];
    }

    void KeyExpander::expand(aes_byte_t* key)
    {
      uint i = 1;
      for (uint j = m_key_length; j < m_expanded_length; j += BLOCK_ROWS)
      {
        aes_byte_t t[BLOCK_ROWS];
        for (uint k = 0; k < BLOCK_ROWS; ++k) {
          t[k] = key[j - BLOCK_ROWS + k];
        }
        if (j % m_key_length == 0) {
          schedule_core(t, i);
          ++i;
        } else if (m_key_length > AES_192_BYTES && j % m_key_length == 4) {
          m_helper.sub_word(t);
        }
        for (uint k = 0; k < BLOCK_ROWS; ++k) {
          key[j + k] = t[k] ^ key[j - m_key_length + k];
        }
      }
    }

  } // namespace AES

} // namespace Crypto
