 #ifndef CRYPTO_KEYREADER_H
#define CRYPTO_KEYREADER_H

#include "Crypto_global.h"

namespace Crypto {
  
  template <typename Key>
  class CRYPTOSHARED_EXPORT KeyReader
  {
  public:
    Key read_key(std::string key_string);

  };
  
}

#endif // CRYPTO_KEYREADER_H
