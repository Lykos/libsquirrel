#ifndef CRYPTO_SHA256HASHER_H
#define CRYPTO_SHA256HASHER_H

#include "Crypto_global.h"

namespace Crypto {
  
  class CRYPTOSHARED_EXPORT SHA256Hasher
  {
  public:
    typedef u_int8_t sha256_byte_t;

    void hash(const sha256_byte_t* message, ulong message_length, sha256_byte_t* digest);

    uint digest_length() const { return 32; }

  };
  
} // namespace Crypto

#endif // CRYPTO_SHA256HASHER_H
