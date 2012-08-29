#ifndef CRYPTO_SHA2HASHER_H
#define CRYPTO_SHA2HASHER_H

#include "Crypto/Crypto_global.h"

#define SHA2_DIGEST_BYTE_SIZE 32

namespace Crypto {
  
  class CRYPTOSHARED_EXPORT SHA2Hasher
  {
  public:
    typedef u_int8_t sha2_byte_t;

    inline explicit SHA2Hasher(uint digest_length = 256): m_digest_length (digest_length) {}

    void hash(const sha2_byte_t* message, ulong message_length, sha2_byte_t* digest) const;

    inline uint digest_length() const { return m_digest_length; }

  private:
    uint m_digest_length;

  };
  
} // namespace Crypto

#endif // CRYPTO_SHA2HASHER_H
