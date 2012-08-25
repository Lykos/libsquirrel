#ifndef CRYPTO_AES_HELPER_H
#define CRYPTO_AES_HELPER_H

namespace Crypto {
  namespace AES {
    
    class Helper
    {
    public:
      apply_round_key(char* cipher, char* key, uint round);

      sub_bytes(char* cipher);

      shift_rows(char* cipher);

      mix_columns(char* cipher);

      rotate_word(char* word);

      sub_word(char* word);

    };
    
  } // namespace AES
} // namespace Crypto

#endif // CRYPTO_AES_HELPER_H
