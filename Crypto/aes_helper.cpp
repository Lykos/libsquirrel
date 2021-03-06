#include "aes_constants.h"
#include "aes_helper.h"
#include <string>
#include <climits>

using namespace std;

namespace Crypto {

  namespace AES {
    
    void Helper::apply_round_key(string& cipher, string& key, number_size_t round)
    {
      for (number_size_t i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] ^= key[i + round * BLOCK_BYTE_SIZE];
      }
    }

    void Helper::sub_bytes(string& cipher)
    {
      for (number_size_t i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] = SBox[byte_t(cipher[i])];
      }
    }

    void Helper::inv_sub_bytes(string& cipher)
    {
      for (number_size_t i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] = InvSBox[byte_t(cipher[i])];
      }
    }

    inline void Helper::shift_row_1(string& cipher, number_size_t row)
    {
      byte_t a;
      a = cipher[row];
      cipher[row] = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = a;
    }

    inline void Helper::shift_row_2(string& cipher, number_size_t row)
    {
      byte_t a = cipher[row];
      cipher[row] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = a;
      a = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = a;
    }

    inline void Helper::shift_row_3(string& cipher, number_size_t row)
    {
      byte_t a = cipher[row];
      cipher[row] = cipher[row + 3 * BLOCK_ROWS];
      cipher[row + 3 * BLOCK_ROWS] = cipher[row + 2 * BLOCK_ROWS];
      cipher[row + 2 * BLOCK_ROWS] = cipher[row + BLOCK_ROWS];
      cipher[row + BLOCK_ROWS] = a;
    }

    void Helper::inv_shift_rows(string& cipher)
    {
      shift_row_1(cipher, 3);
      shift_row_2(cipher, 2);
      shift_row_3(cipher, 1);
    }

    void Helper::shift_rows(string& cipher)
    {
      shift_row_1(cipher, 1);
      shift_row_2(cipher, 2);
      shift_row_3(cipher, 3);
    }

    inline byte_t Helper::rijndael_mult(byte_t a, byte_t b)
    {
      // Zero[] trick is needed because in cryptographic code, one should not use branches that depend on the input.
      return Exp[(Log[a] + Log[b]) % 255] * Invertible[a] * Invertible[b];
    }

    void Helper::mult_columns(string& cipher, const string& factor)
    {
      for (number_size_t c = 0; c < BLOCK_COLS; ++c) {
        byte_t temp[4];
        for (number_size_t r = 0; r < 4; ++r) {
          temp[r] = rijndael_mult(cipher[r + c * BLOCK_COLS], factor[0])
              ^ rijndael_mult(cipher[(r + 1) % 4 + c * BLOCK_COLS], factor[1])
              ^ rijndael_mult(cipher[(r + 2) % 4 + c * BLOCK_COLS], factor[2])
              ^ rijndael_mult(cipher[(r + 3) % 4 + c * BLOCK_COLS], factor[3]);
        }
        for (number_size_t r = 0; r < 4; ++r) {
          cipher[r + c * BLOCK_COLS] = temp[r];
        }
      }
    }

    void Helper::mix_columns(string& cipher)
    {
      static const string a ({2, 3, 1, 1});
      mult_columns(cipher, a);
    }

    void Helper::inv_mix_columns(string& cipher)
    {
      static const string a ({0xe, 0xb, 0xd, 0x9});
      mult_columns(cipher, a);
    }

    void Helper::rotate_word(string& word)
    {
      byte_t a = word[0];
      word[0] = word[1];
      word[1] = word[2];
      word[2] = word[3];
      word[3] = a;
    }

    void Helper::sub_word(string& word)
    {
      for (number_size_t i = 0; i < BLOCK_ROWS; ++i) {
        word[i] = SBox[byte_t(word[i])];
      }
    }
    
  } // namespace AES

} // namespace Crypto
