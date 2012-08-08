#ifndef DECRYPTER_H
#define DECRYPTER_H

#include "Crypto_global.h"
#include "key.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT Decrypter
  {
  public:

    Key::text_t decrypt(Key::text_t);
  };

}

#endif // DECRYPTER_H
