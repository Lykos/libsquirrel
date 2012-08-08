#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include "Crypto_global.h"
#include "key.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT Encrypter
  {
  public:
    Key::text_t encrypt(Key::text_t) const = 0;
  };

}

#endif // ENCRYPTER_H
