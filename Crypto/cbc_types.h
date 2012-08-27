#ifndef CRYPTO_CBC_TYPES_H
#define CRYPTO_CBC_TYPES_H

#include "Crypto_global.h"

namespace Crypto {

 namespace CBC {

   typedef u_int8_t cbc_byte_t;

   template <typename BlockCipher>
   class CRYPTOSHARED_EXPORT Decrypter;

   template <typename BlockCipher>
   class CRYPTOSHARED_EXPORT Encrypter;

 }

}

#endif // CRYPTO_CBC_TYPES_H
