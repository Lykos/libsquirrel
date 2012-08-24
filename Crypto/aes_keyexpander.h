#ifndef CRYPTO_AES_KEYEXPANDER_H
#define CRYPTO_AES_KEYEXPANDER_H

#include "Crypto_global.h"
#include "aes_types.h"

namespace Crypto {

  namespace AES {
    
    class KeyExpander
    {
    public:
      void expand(const key_t& key, ex_key_t& result) const;
    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_KEYEXPANDER_H
