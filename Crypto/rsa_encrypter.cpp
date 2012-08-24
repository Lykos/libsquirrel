#include "rsa_encrypter.h"

namespace Crypto {

  namespace RSA {

    cipher_text_t Encrypter::encrypt(const plain_text_t& plain_text)
    {
      return plain_text.pow_mod(CryptoEncrypter::m_public_key.exponent, CryptoEncrypter::m_public_key.modulus);
    }


  }
}
