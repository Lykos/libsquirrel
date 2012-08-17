#ifndef CRYPTO_KEYPAIR_H
#define CRYPTO_KEYPAIR_H

namespace Crypto {
  
  template <typename PublicKey, typename PrivateKey>
  struct KeyPair
  {
    inline KeyPair() {}

    inline KeyPair(const KeyPair<PublicKey, PrivateKey>& other): public_key (other.public_key), private_key (other.private_key) {}

    inline KeyPair(const PublicKey& pub, const PrivateKey priv): public_key (pub), private_key (priv) {}

    inline KeyPair<PublicKey, PrivateKey>& operator=(const KeyPair<PublicKey, PrivateKey>& other) { public_key = other.public_key; private_key = other.private_key; return *this; }

    PublicKey public_key;

    PrivateKey private_key;
  };
  
} // namespace Crypto

#endif // CRYPTO_KEYPAIR_H
