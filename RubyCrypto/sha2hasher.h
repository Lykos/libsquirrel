#ifndef SHA2HASHER_H
#define SHA2HASHER_H

#ifdef __cplusplus

#include "Crypto/sha2hasher.h"
#include <rice/Data_Type.hpp>

extern Rice::Data_Type<Crypto::SHA2Hasher> rb_cSHA2Hasher;

extern "C" {
#endif

void Init_SHA2Hasher();

#ifdef __cplusplus
}
#endif

#endif // SHA2HASHER_H
