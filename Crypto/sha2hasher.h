#ifndef CRYPTO_SHA2HASHER_H
#define CRYPTO_SHA2HASHER_H

#include "Crypto_global.h"
#include "types.h"
#include <string>

namespace Crypto {
  
  class CRYPTOSHARED_EXPORT SHA2Hasher
  {
  public:
    inline explicit SHA2Hasher(number_size_t digest_length = 256): m_digest_length (digest_length) {}

    std::string hash(const std::string& message) const;

    inline number_size_t digest_length() const { return m_digest_length; }

  private:
    number_size_t m_digest_length;

  };
  
} // namespace Crypto

#endif // CRYPTO_SHA2HASHER_H
