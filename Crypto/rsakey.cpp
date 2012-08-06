#include "rsakey.h"

namespace Crypto {

  RSAKey::RSAKey(exponent_t exponent, const number_t& modulus):
    m_exponent(exponent), m_modulus (modulus)
  {
  }

}
