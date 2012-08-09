#ifndef RSAPQSTRATEGY_H
#define RSAPQSTRATEGY_H

#include "rsakey.h"
#include "rsastrategy.h"

namespace Crypto {

  class RSAPQStrategy : public RSAStrategy
  {
  public:
    RSAPQStrategy(const RSAKey& secret_key, const RSAKey::text_t& p, const RSAKey::text_t& q);

    RSAKey::text_t encrypt(const RSAKey::text_t& plain_text) const;

    RSAPQStrategy* copy() const;

  private:

    RSAKey m_secret_key;

    RSAKey::text_t m_p;

    RSAKey::text_t m_q;

    RSAKey::text_t m_p_inv;

    RSAKey::text_t m_q_inv;

  };

}

#endif // RSAPQSTRATEGY_H
