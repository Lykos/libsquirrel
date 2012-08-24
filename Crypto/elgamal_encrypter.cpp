#include "elgamal_encrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    cipher_text_t Encrypter::encrypt(const plain_text_t& plain_text)
    {
      const number_t& modulus = CryptoEncrypter::m_public_key.modulus;
      const number_t& generator = CryptoEncrypter::m_public_key.modulus;
      const number_t& public_gen_power = CryptoEncrypter::m_public_key.gen_power;
      exponent_t exponent = rand_number(modulus);
      number_t own_gen_power = generator.pow_mod(exponent, modulus);
      number_t key = public_gen_power.pow_mod(exponent, modulus);
      number_t key_inv = key.mult_inv_mod(modulus);
      number_t text = (plain_text * key_inv) % modulus;
      return {text, own_gen_power};
    }
    
  } // namespace Elgamal

} // namespace Crypto
