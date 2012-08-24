#include "Crypto_global.h"
#include "aes_constants.h"
#include "aes_helper.h"

namespace Crypto {

  namespace AES {
    
    void Helper::apply_round_key(char* cipher, char* key, uint round)
    {
      for (uint i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] ^= key[i + round * BLOCK_BYTE_SIZE];
      }
    }

    void Helper::sub_bytes(char* cipher)
    {
      for (uint i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] = SBox[cipher[i]];
      }
    }

    void Helper::shift_rows(char* cipher)
    {
      for (uint r = 1; r < 4; ++r) {
        a = cipher[r];
        for (uint c = 0; c < 4; ++c) {

        }
      }
    }

    void Helper::rotate_word(char* word)
    {
      a = word[0];
      word[0] = word[1];
    }
    
  } // namespace AES

} // namespace Crypto
