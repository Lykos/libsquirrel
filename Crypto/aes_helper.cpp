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

    void Helper::inv_sub_bytes(char* cipher)
    {
      for (uint i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] = InvSBox[(unsigned char)(cipher[i])];
      }
    }

    inline void Helper::shift_row_1(char* cipher, uint row)
    {
      char a;
      a = cipher[row];
      cipher[row] = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = a;
    }

    inline void Helper::shift_row_2(char* cipher, uint row)
    {
      char a = cipher[row];
      cipher[row] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = a;
      a = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = a;
    }

    inline void Helper::shift_row_3(char* cipher, uint row)
    {
      char a = cipher[row];
      cipher[row] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = a;
    }

    void Helper::inv_shift_rows(char* cipher)
    {
      shift_row_1(cipher, 3);
      shift_row_2(cipher, 2);
      shift_row_3(cipher, 1);
    }

    void Helper::shift_rows(char* cipher)
    {
      shift_row_1(cipher, 1);
      shift_row_2(cipher, 2);
      shift_row_3(cipher, 3);
    }

    inline char Helper::rijndael_mult(unsigned char a, unsigned char b)
    {
      // Zero[] trick is needed because in cryptographic code, one should not use branches that depend on the input.
      return Exp[(Log[a] + Log[b]) % 255] * Invertible[a] * Invertible[b];
    }

    void Helper::mult_columns(char* cipher, char* factor)
    {
      for (uint c = 0; c < BLOCK_COLS; ++c) {
        char temp[4];
        for (uint r = 0; r < 4; ++r) {
          temp[r] = rijndael_mult(cipher[r + c * BLOCK_COLS], factor[0])
              ^ rijndael_mult(cipher[(r + 1) % 4 + c * BLOCK_COLS], factor[1])
              ^ rijndael_mult(cipher[(r + 2) % 4 + c * BLOCK_COLS], factor[2])
              ^ rijndael_mult(cipher[(r + 3) % 4 + c * BLOCK_COLS], factor[3]);
        }
        for (uint r = 0; r < 4; ++r) {
          cipher[r + c * BLOCK_COLS] = temp[r];
        }
      }
    }

    void Helper::mix_columns(char* cipher)
    {
      char a[] = {2, 3, 1, 1};
      mult_columns(cipher, a + 0);
    }

    void Helper::inv_mix_columns(char* cipher)
    {
      char a[] = {0xe, 0xb, 0xd, 0x9};
      mult_columns(cipher, a + 0);
    }

    void Helper::rotate_word(char* word)
    {
      char a = word[0];
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
