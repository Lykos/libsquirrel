#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename T>
  class CRYPTOSHARED_EXPORT KeyGenerator
  {
  public:
    virtual T generate() const = 0;
  };

}

#endif // KEYGENERATOR_H
