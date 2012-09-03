#ifndef CRYPTO_AES_HELPER_H
#define CRYPTO_AES_HELPER_H

#include "Crypto/types.h"

namespace Crypto {

  namespace AES {
    
    class Helper
    {
    private:
      inline void shift_row_1(byte_t* cipher, uint row);

      inline void shift_row_2(byte_t* cipher, uint row);

      inline void shift_row_3(byte_t* cipher, uint row);

      inline byte_t rijndael_mult(byte_t a, byte_t b);

      inline void mult_columns(byte_t* cipher, byte_t* factor);

    public:
      void apply_round_key(byte_t* cipher, byte_t* key, uint round);

      void sub_bytes(byte_t* cipher);

      void shift_rows(byte_t* cipher);

      void mix_columns(byte_t* cipher);

      void inv_sub_bytes(byte_t* cipher);

      void inv_shift_rows(byte_t* cipher);

      void inv_mix_columns(byte_t* cipher);

      void rotate_word(byte_t* word);

      void sub_word(byte_t* word);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_HELPER_H
