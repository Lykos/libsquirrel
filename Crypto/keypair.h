#ifndef KEYPAIR_H
#define KEYPAIR_H

#include "Crypto_global.h"
#include "key.h"

namespace Crypto {

  template <typename T>
  class CRYPTOSHARED_EXPORT KeyPair
  {
  public:
    KeyPair(const T& public_key, const T& secret_key);

    inline const T& get_public_key() const;

    inline const T& get_secret_key() const;

  private:
    T m_public_key;
    T m_secret_key;
  };

}

#endif // KEYPAIR_H
