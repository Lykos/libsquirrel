#include "rsapqstrategy.h"

namespace Crypto {

  RSAPQStrategy::RSAPQStrategy(const RSAKey& secret_key, const RSAKey::text_t& p, const RSAKey::text_t& q):
    m_secret_key (secret_key),
    m_p (p),
    m_q (q)
  {
  }

  RSAKey::text_t RSAPQStrategy::encrypt(const RSAKey::text_t& plain_text) const
  {
    return plain_text.pow_mod(m_secret_key.get_exponent(), m_secret_key.get_modulus());
  }

  RSAPQStrategy* RSAPQStrategy::copy() const
  {
    return new RSAPQStrategy(m_secret_key, m_p, m_q);
  }

}
