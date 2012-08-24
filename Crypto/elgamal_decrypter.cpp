#include "elgamal_decrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    plain_text_t Decrypter::decrypt(const cipher_text_t &cipher_text)
    {
      exponent_t exponent = CryptoDecrypter::m_private_key.exponent;
      number_t modulus = CryptoDecrypter::m_private_key.modulus;
      number_t key = cipher_text.gen_power.pow_mod(exponent, modulus);
      return (cipher_text.text * key) % modulus;
    }
    
  } // namespace Elgamal

} // namespace Crypto
