#include "Crypto/aes_keyexpander.h"
#include "Crypto/aes_constants.h"
#include "Crypto/types.h"
#include "Crypto/preconditionviolation.h"
#include <climits>
#include <stdexcept>
#include <string>

using namespace std;

namespace Crypto {

  namespace AES {


    inline number_size_t KeyExpander::expanded_length(number_size_t key_length)
    {
      return (rounds(key_length) + 1) * BLOCK_BYTE_SIZE;
    }

    inline number_size_t KeyExpander::rounds(number_size_t key_length)
    {
      PREC(KeyLength, key_length == AES_128_BYTES || key_length == AES_192_BYTES || key_length == AES_256_BYTES);
      if (key_length == AES_128_BYTES) {
        return AES_128_ROUNDS;
      } else if (key_length == AES_192_BYTES) {
        return AES_192_ROUNDS;
      } else {
        return AES_256_ROUNDS;
      }
    }

    inline void KeyExpander::schedule_core(string& in, uint i)
    {
      m_helper.rotate_word(in);
      m_helper.sub_word(in);
      in[0] ^= Rcon[i];
    }

    string KeyExpander::expand(const string& key)
    {
      number_size_t key_length = key.length();
      number_size_t expanded_key_length = expanded_length(key_length);
      string expanded_key (key);
      expanded_key.resize(expanded_key_length);
      uint i = 1;
      for (uint j = key_length; j < expanded_key_length; j += BLOCK_ROWS)
      {
        string t = expanded_key.substr(j - BLOCK_ROWS, BLOCK_ROWS);
        if (j % key_length == 0) {
          schedule_core(t, i);
          ++i;
        } else if (key_length > AES_192_BYTES && j % key_length == 4) {
          m_helper.sub_word(t);
        }
        for (uint k = 0; k < BLOCK_ROWS; ++k) {
          expanded_key[j + k] = t[k] ^ expanded_key[j - key_length + k];
        }
      }
      return expanded_key;
    }

  } // namespace AES

} // namespace Crypto
