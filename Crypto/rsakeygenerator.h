#ifndef RSAKEYGENERATOR_H
#define RSAKEYGENERATOR_H

#include "Crypto_global.h"
#include "keygenerator.h"
#include "rsakeypair.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSAKeyGenerator : public KeyGenerator<RSAKeyPair>
  {
  public:
    RSAKeyGenerator();

    RSAKeyPair generate() const;

  };

}

#endif // RSAKEYGENERATOR_H
