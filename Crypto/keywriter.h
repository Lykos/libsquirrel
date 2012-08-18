#ifndef CRYPTO_KEYWRITER_H
#define CRYPTO_KEYWRITER_H

#include "Crypto_global.h"

namespace Crypto {

  template <typename Key>
  class CRYPTOSHARED_EXPORT KeyReader
  {
  public:
    std::string write_key(Key key);
  };

}

#endif // CRYPTO_KEYWRITER_H
