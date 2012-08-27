#ifndef CRYPTO_SHA256HASHER_H
#define CRYPTO_SHA256HASHER_H

#include "Crypto_global.h"

namespace Crypto {
  
  class SHA256Hasher
  {
  public:
    void hash(char* message, ulong message_length, char* digest);

  };
  
} // namespace Crypto

#endif // CRYPTO_SHA256HASHER_H
