#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename PublicKey, typename Plain, typename Cipher>
  class CRYPTOSHARED_EXPORT Encrypter
  {
  public:
    inline Encrypter(PublicKey public_key): m_public_key (public_key) {}

    inline Encrypter(const Encrypter<PublicKey, Plain, Cipher>& other): m_public_key (other.m_public_key) {}

    inline Encrypter<PublicKey, Plain, Cipher>& operator=(const Encrypter<PublicKey, Plain, Cipher>& other) { m_public_key = other.m_public_key; return *this; }

    virtual Cipher encrypt(const Plain& plain) const = 0;

  protected:
    PublicKey m_public_key;
  };

}

#endif // ENCRYPTER_H
