#ifndef CRYPTO_ENCRYPTER_H
#define CRYPTO_ENCRYPTER_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename PublicKey, typename Plain, typename Cipher>
  class CRYPTOSHARED_EXPORT Encrypter
  {
  public:
    inline Encrypter(const PublicKey& public_key): m_public_key (public_key) {}

    virtual Cipher encrypt(const Plain& plain) = 0;

  protected:
    PublicKey m_public_key;
  };

} // namespace Crypto

#endif // CRYPTO_ENCRYPTER_H
