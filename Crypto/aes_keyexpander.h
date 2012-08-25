#ifndef CRYPTO_AES_KEYEXPANDER_H
#define CRYPTO_AES_KEYEXPANDER_H

#include "Crypto_global.h"
#include "aes_helper.h"

namespace Crypto {

  namespace AES {
    
    class KeyExpander
    {
    private:
      Helper m_helper;

    public:      
      void expand(char* key, uint key_length) const;

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_KEYEXPANDER_H
