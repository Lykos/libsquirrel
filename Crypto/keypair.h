#ifndef CRYPTO_KEYPAIR_H
#define CRYPTO_KEYPAIR_H

namespace Crypto {
  
  template <typename PublicKey, typename PrivateKey>
  struct KeyPair
  {
    inline KeyPair() {}

    inline KeyPair(const PublicKey& pub, const PrivateKey& priv): public_key (pub), private_key (priv) {}

    PublicKey public_key;

    PrivateKey private_key;
  };
  
} // namespace Crypto

#endif // CRYPTO_KEYPAIR_H
