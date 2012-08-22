#ifndef CRYPTO_KEYPAIR_H
#define CRYPTO_KEYPAIR_H

#include "Crypto_global.h"

namespace Crypto {
  
  template <typename PublicKey, typename PrivateKey>
  struct CRYPTOSHARED_EXPORT KeyPair
  {
    inline KeyPair() {}

    inline KeyPair(const PublicKey& pub, const PrivateKey priv): public_key (pub), private_key (priv) {}

    PublicKey public_key;

    PrivateKey private_key;
  };
  
} // namespace Crypto

#endif // CRYPTO_KEYPAIR_H
