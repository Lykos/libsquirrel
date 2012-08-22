#ifndef CRYPTO_DECRYPTER_H
#define CRYPTO_DECRYPTER_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename PrivateKey, typename Plain, typename Cipher>
  class CRYPTOSHARED_EXPORT Decrypter
  {
  public:
    inline Decrypter(PrivateKey private_key): m_private_key (private_key) {}

    virtual Plain decrypt(const Cipher& cipher_text) const = 0;

  protected:
    PrivateKey m_private_key;

  };

} // namespace Crypto

#endif // CRYPTO_DECRYPTER_H
