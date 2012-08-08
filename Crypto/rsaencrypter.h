#ifndef RSA_H
#define RSA_H

#include "rsastrategy.h"
#include "rsakey.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSAEncrypter
  {
  public:

    RSAEncrypter(const RSAKey& secret_key);

    RSAEncrypter(const RSAKey& secret_key, const RSAKey::text_t& p, const RSAKey::text_t& q);

    RSAEncrypter& operator=(const RSAEncrypter& other);

    RSAKey::text_t encrypt(const RSAKey::text_t& number);

    virtual ~RSAEncrypter();

  private:
    RSAStrategy *m_strategy;

  };

}

#endif // RSA_H
