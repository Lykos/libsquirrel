#ifndef RSAKEYPAIR_H
#define RSAKEYPAIR_H

#include "Crypto_global.h"
#include "keypair.h"
#include "rsakey.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSAKeyPair : public KeyPair<RSAKey>
  {
  public:
    RSAKeyPair(const RSAKey& public_key, const RSAKey& secret_key, const RSAKey::text_t& p, const RSAKey::text_t& q);

    inline const RSAKey::text_t& get_p() const;

    inline const RSAKey::text_t& get_q() const;

  private:

    RSAKey::text_t m_p;

    RSAKey::text_t m_q;

  };

}

#endif // RSAKEYPAIR_H
