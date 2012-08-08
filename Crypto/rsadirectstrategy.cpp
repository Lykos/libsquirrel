#include "rsadirectstrategy.h"

namespace Crypto {

  RSADirectStrategy::RSADirectStrategy(const RSAKey& secret_key):
    m_secret_key (secret_key)
  {
  }

  RSAKey::text_t RSADirectStrategy::encrypt(const RSAKey::text_t& plain_text) const
  {
    return plain_text.pow_mod(m_secret_key.get_exponent(), m_secret_key.get_modulus());
  }

  RSADirectStrategy* RSADirectStrategy::copy() const
  {
    return new RSADirectStrategy(m_secret_key);
  }

}
