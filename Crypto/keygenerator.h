#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename PublicKey, typename PrivateKey>
  class CRYPTOSHARED_EXPORT KeyGenerator
  {
  public:
    typedef std::pair<PublicKey, PrivateKey> key_pair_t;

    virtual key_pair_t generate() const = 0;
  };

}

#endif // KEYGENERATOR_H
