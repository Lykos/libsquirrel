#include "rsadecrypter.h"

namespace Crypto {

  RSADecrypter::RSADecrypter(const RSAKey& public_key):
    m_public_key (public_key)
  {
  }

  RSAKey::text_t RSADecrypter::decrypt(const RSAKey::text_t& cipher_text) const
  {
    return cipher_text.pow_mod(m_public_key.get_exponent(), m_public_key.get_modulus());
  }

}
