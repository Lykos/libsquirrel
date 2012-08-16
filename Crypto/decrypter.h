#ifndef DECRYPTER_H
#define DECRYPTER_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename PrivateKey, typename Plain, typename Cipher>
  class CRYPTOSHARED_EXPORT Decrypter
  {
  public:
    inline Decrypter(PrivateKey private_key): m_private_key (private_key) {}

    inline Decrypter(const Decrypter<PrivateKey, Plain, Cipher>& other): m_private_key (other.m_private_key) {}

    inline Decrypter<PrivateKey, Plain, Cipher>& operator=(const Decrypter<PrivateKey, Plain, Cipher>& other) { m_private_key = other.m_private_key; return *this; }

    virtual Plain decrypt(const Cipher& cipher) = 0;

  protected:
    PrivateKey m_private_key;

  };

}

#endif // DECRYPTER_H
