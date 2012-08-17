#include "elgamal_encrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    cipher_text_t Encrypter::encrypt(const plain_text_t& plain_text) const
    {
      number_t text = (plain_text * CryptoEncrypter::m_public_key.key_inv) % CryptoEncrypter::m_public_key.modulus;
      cipher_text_t cipher_text {text, CryptoEncrypter::m_public_key.gen_power};
      return cipher_text;
    }
    
  } // namespace Elgamal

} // namespace Crypto
