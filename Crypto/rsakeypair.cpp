#include "rsakeypair.h"

namespace Crypto {

  RSAKeyPair::RSAKeyPair(const RSAKey& public_key, const RSAKey& secret_key, const Key::text_t& p, const Key::text_t& q):
    KeyPair (public_key, secret_key),
    m_p (p),
    m_q (q)
  {
  }

  inline const RSAKey::text_t& RSAKeyPair::get_p() const
  {
    return m_p;
  }

  inline const RSAKey::text_t& RSAKeyPair::get_q() const
  {
    return m_q;
  }

}
