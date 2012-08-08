#include "rsakey.h"

namespace Crypto {

  RSAKey::RSAKey(exponent_t exponent, const text_t& modulus):
    m_exponent(exponent), m_modulus (modulus)
  {
  }

  inline RSAKey::exponent_t RSAKey::get_exponent() const
  {
    return m_exponent;
  }

  inline const RSAKey::text_t& RSAKey::get_modulus() const
  {
    return m_modulus;
  }

}
