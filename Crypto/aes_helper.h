#ifndef CRYPTO_AES_HELPER_H
#define CRYPTO_AES_HELPER_H

#include "Crypto/aes_types.h"

namespace Crypto {

  namespace AES {
    
    class Helper
    {
    private:
      inline void shift_row_1(aes_byte_t* cipher, uint row);

      inline void shift_row_2(aes_byte_t* cipher, uint row);

      inline void shift_row_3(aes_byte_t* cipher, uint row);

      inline aes_byte_t rijndael_mult(aes_byte_t a, aes_byte_t b);

      inline void mult_columns(aes_byte_t* cipher, aes_byte_t* factor);

    public:
      void apply_round_key(aes_byte_t* cipher, aes_byte_t* key, uint round);

      void sub_bytes(aes_byte_t* cipher);

      void shift_rows(aes_byte_t* cipher);

      void mix_columns(aes_byte_t* cipher);

      void inv_sub_bytes(aes_byte_t* cipher);

      void inv_shift_rows(aes_byte_t* cipher);

      void inv_mix_columns(aes_byte_t* cipher);

      void rotate_word(aes_byte_t* word);

      void sub_word(aes_byte_t* word);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_HELPER_H
