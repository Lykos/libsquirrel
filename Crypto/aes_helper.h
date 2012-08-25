#ifndef CRYPTO_AES_HELPER_H
#define CRYPTO_AES_HELPER_H

namespace Crypto {
  namespace AES {
    
    class Helper
    {
    private:
      inline void shift_row_1(char* cipher, uint row);

      inline void shift_row_2(char* cipher, uint row);

      inline void shift_row_3(char* cipher, uint row);

      inline char rijndael_mult(unsigned char a, unsigned char b);

      inline void mult_columns(char* cipher, char* factor);

    public:
      void apply_round_key(char* cipher, char* key, uint round);

      void sub_bytes(char* cipher);

      void shift_rows(char* cipher);

      void mix_columns(char* cipher);

      void inv_sub_bytes(char* cipher);

      void inv_shift_rows(char* cipher);

      void inv_mix_columns(char* cipher);

      void rotate_word(char* word);

      void sub_word(char* word);

    };
    
  } // namespace AES
} // namespace Crypto

#endif // CRYPTO_AES_HELPER_H
