#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include "Crypto_global.h"
#include "basetypes.h"

namespace Crypto {

  template <typename KeyPair>
  class CRYPTOSHARED_EXPORT KeyGenerator
  {
  public:
    virtual KeyPair generate(DataStructures::index_type number_bits) const = 0;
  };

}

#endif // KEYGENERATOR_H
