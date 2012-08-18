#ifndef CRYPTO_KEYPERSONALIZER_H
#define CRYPTO_KEYPERSONALIZER_H

#include "Crypto_global.h"

namespace Crypto {
  
  template <typename Key, typename PersonalizedKey>
  class CRYPTOSHARED_EXPORT KeyPersonalizer
  {
  public:
    virtual PersonalizedKey personalize_key(Key key) const = 0;

  };
  
} // namespace Crypto

#endif // CRYPTO_KEYPERSONALIZER_H
