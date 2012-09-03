#ifndef CRYPTO_SHA2HASHER_H
#define CRYPTO_SHA2HASHER_H

#include "Crypto/Crypto_global.h"
#include <string>

namespace Crypto {
  
  class CRYPTOSHARED_EXPORT SHA2Hasher
  {
  public:
    inline explicit SHA2Hasher(uint digest_length = 256): m_digest_length (digest_length) {}

    std::string hash(const std::string& message) const;

    inline uint digest_length() const { return m_digest_length; }

  private:
    uint m_digest_length;

  };
  
} // namespace Crypto

#endif // CRYPTO_SHA2HASHER_H
