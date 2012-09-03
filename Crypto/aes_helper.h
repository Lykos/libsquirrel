#ifndef CRYPTO_AES_HELPER_H
#define CRYPTO_AES_HELPER_H

#include "types.h"
#include <string>

namespace Crypto {

  namespace AES {
    
    class Helper
    {
    private:
      inline void shift_row_1(std::string& cipher, uint row);

      inline void shift_row_2(std::string& cipher, uint row);

      inline void shift_row_3(std::string& cipher, uint row);

      inline byte_t rijndael_mult(byte_t a, byte_t b);

      inline void mult_columns(std::string& cipher, const std::string& factor);

    public:
      void apply_round_key(std::string& cipher, std::string& key, uint round);

      void sub_bytes(std::string& cipher);

      void shift_rows(std::string& cipher);

      void mix_columns(std::string& cipher);

      void inv_sub_bytes(std::string& cipher);

      void inv_shift_rows(std::string& cipher);

      void inv_mix_columns(std::string& cipher);

      void rotate_word(std::string& word);

      void sub_word(std::string& word);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_HELPER_H
