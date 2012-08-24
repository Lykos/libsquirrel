#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <climits>
#include <cassert>
#include <cstring>

namespace Crypto {

  namespace AES {

    inline word_t schedule_core(word_t in, uint i)
    {
      return (SBox[in & 0xFF] << 3 * CHAR_BIT)
          + (SBOX[(in >> 3 * CHAR_BIT) & 0xFF] << 2 * CHAR_BIT)
          + (SBOX[(in >> 2 * CHAR_BIT) & 0xFF] << CHAR_BIT)
          + (SBOX[(in >> CHAR_BIT) & 0xFF] ^ Rcon[i]);
    }

    void KeyExpander::expand(const key_t& key, ex_key_t& result) const
    {
      result.key_length = key.key_length;
      uint key_length = key.key_length;
      uint rounds;
      if (key_length == AES_128_BYTES) {
        rounds = AES_128_ROUNDS;
      } else if (key_length == AES_192_BYTES) {
        rounds = AES_192_ROUNDS;
      } else if (key_length == AES_256_BYTES) {
        rounds = AES_256_ROUNDS;
      } else {
        throw new logic_error("Invalid key length.");
      }
      uint j = 0;
      for (; j < key_length; ++j) {
        result.bytes[j] = key.bytes[j];
      }
      uint i = 1;
      for (; j < (rounds + 1) * BLOCK_SIZE;)
      {
        char_t t[4];
        for (uint k = 0; k < 4; ++k) {
          t[k] = result.bytes[j - 4 + k];
        }
        if (j % BLOCK_SIZE == 0) {
          schedule_core(t, i);
          ++i;
        }
        for (uint k = 0; k < 16; ++k) {
          result.bytes[j + k] = t[k % 4] ^ result.bytes[j];
        }
      }
    }

  } // namespace AES

} // namespace Crypto
