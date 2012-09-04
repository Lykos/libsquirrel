#ifndef SHA2HASHER_H
#define SHA2HASHER_H

#ifdef __cplusplus

#include "Crypto/sha2hasher.h"
#include <rice/Data_Type.hpp>

class SHA2Hasher {
public:
  SHA2Hasher(Crypto::number_size_t digest_size = 256): m_hasher (digest_size) {}

  std::string hash(const std::string& message);

private:
  Crypto::SHA2Hasher m_hasher;

};

extern Rice::Data_Type<SHA2Hasher> rb_cSHA2Hasher;

extern "C" {
#endif

void Init_SHA2Hasher();

#ifdef __cplusplus
}
#endif

#endif // SHA2HASHER_H
