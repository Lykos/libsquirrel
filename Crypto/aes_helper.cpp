#include "Crypto_global.h"
#include "aes_constants.h"
#include "aes_helper.h"
#include <climits>

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
        cipher[i] = SBox[(unsigned char)(cipher[i])];
      }
    }

    void Helper::shift_rows(char* cipher)
    {
      char a;
      // row 0 stays
      // row 1
      a = cipher[1];
      cipher[1] = cipher[1 + BLOCK_ROWS];
      cipher[1 + BLOCK_ROWS] = cipher[1 + 2 * BLOCK_ROWS];
      cipher[1 + 2 * BLOCK_ROWS] = cipher[1 + 3 * BLOCK_ROWS];
      cipher[1 + 3 * BLOCK_ROWS] = a;
      // row 2
      a = cipher[2];
      cipher[2] = cipher[2 + 2 * BLOCK_ROWS];
      cipher[2 + 2 * BLOCK_ROWS] = a;
      a = cipher[2 + BLOCK_ROWS];
      cipher[2 + BLOCK_ROWS] = cipher[2 + 3 * BLOCK_ROWS];
      cipher[2 + 3 * BLOCK_ROWS] = a;
      // row 3
      a = cipher[3];
      cipher[3] = cipher[3 + 3 * BLOCK_ROWS];
      cipher[3 + 3 * BLOCK_ROWS] = cipher[3 + 2 * BLOCK_ROWS];
      cipher[3 + 2 * BLOCK_ROWS] = cipher[3 + BLOCK_ROWS];
      cipher[3 + BLOCK_ROWS] = a;
    }

    inline char rijndael_multiply(char a, char b)
    {
      // Zero[] trick is needed because in cryptographic code, one should not use branches that depend on the input.
      Exp[(Log[(unsigned char)(a)] + Log[(unsigned char)(b)]) % 255] * Invertible[a] * Invertible[b];
    }

    void Helper::mix_columns(char* cipher)
    {
      for (uint c = 0; c < BLOCK_COLS; ++c) {
        char temp[4];
        for (uint r = 0; r < 4; ++r) {
          temp[r] = rijndael_multiply(cipher[r + c * BLOCK_COLS], 2)
              ^ rijndael_multiply(cipher[(r + 1) % 4 + c * BLOCK_COLS], 3)
              ^ rijndael_multiply(cipher[(r + 2) % 4 + c * BLOCK_COLS], 1)
              ^ rijndael_multiply(cipher[(r + 3) % 4 + c * BLOCK_COLS], 1);
        }
        for (uint r = 0; r < 4; ++r) {
          cipher[r + c * BLOCK_COLS] = temp[r];
        }
      }
    }

    void Helper::rotate_word(char* word)
    {
      a = word[0];
      word[0] = word[1];
      word[1] = word[2];
      word[2] = word[3];
      word[3] = a;
    }

    void Helper::sub_word(char* word)
    {
      for (uint i = 0; i < BLOCK_ROWS; ++i) {
        word[i] = SBox[(unsigned char)(word[i])];
      }
    }
    
  } // namespace AES

} // namespace Crypto
