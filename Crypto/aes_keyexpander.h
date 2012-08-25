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

      uint m_key_length;

      uint m_rounds;

      uint m_expanded_length;

      inline void schedule_core(char* cipher, uint i);

    public:
      KeyExpander(uint key_length);

      inline uint expanded_length() const { return m_expanded_length; }

      inline uint rounds() const { return m_rounds; }

      void expand(char* key);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_KEYEXPANDER_H
