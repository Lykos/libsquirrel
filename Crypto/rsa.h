#ifndef RSA_H
#define RSA_H

#include "rsakey.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSA
  {
  public:
    RSA();

    RSA(const RSAKey& secret_key, const RSAKey& public_key);

    RSA(const RSAKey& secret_key, const RSAKey& public_key, RSAKey::number_t p, RSAKey::number_t q);

    operator=(const RSA& other);

    RSAKey::number_t encrypt(const RSAKey::number_t& number);

    RSAKey::number_t decrypt(const RSAKey::number_t& number);

    RSAKey get_public_key() const;

    RSAKey get_secret_key() const;

    bool p_q_defined() const;

    RSAKey::number_t get_p() const;

    RSAKey::number_t get_q() const;

    virtual ~RSA();

  private:
    RSAKey m_public_key;
    RSAKey m_secret_key;
    RSAStrategy *m_strategy;

  };

}

#endif // RSA_H
