#include "rsapqstrategy.h"

namespace Crypto {

  RSAPQStrategy::RSAPQStrategy(const RSAKey& secret_key, const RSAKey::text_t& p, const RSAKey::text_t& q):
    m_secret_key (secret_key),
    m_p (p),
    m_q (q),
    m_p_inv (p.inv_mod(q)),
    m_q_inv (q.inv_mod(p))
  {
    assert(p * q == secret_key.get_modulus());
  }

  RSAKey::text_t RSAPQStrategy::encrypt(const RSAKey::text_t& plain_text) const
  {
    // According to precalculated inverses for chinese remainder theorem
    RSAKey::text_t mod_p = plain_text.pow_mod(m_secret_key.get_exponent(), m_p);
    RSAKey::text_t mod_q = plain_text.pow_mod(m_secret_key.get_exponent(), m_q);
    RSAKey::text_t p_factor = (mod_p * m_q_inv) % m_p;
    RSAKey::text_t q_factor = (mod_q * m_p_inv) % m_q;
    return (p_factor * m_q + q_factor * m_p) % m_secret_key.get_modulus();
  }

  RSAPQStrategy* RSAPQStrategy::copy() const
  {
    return new RSAPQStrategy(m_secret_key, m_p, m_q);
  }

}
