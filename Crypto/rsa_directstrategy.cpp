#include "rsa_directstrategy.h"

namespace Crypto {

  namespace RSA {

    plain_text_t DirectStrategy::decrypt(const cipher_text_t& cipher_text) const
    {
      return cipher_text.pow_mod(m_private_key.exponent, m_private_key.modulus);
    }

  }

}
