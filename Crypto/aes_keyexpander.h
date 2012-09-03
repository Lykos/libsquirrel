#ifndef CRYPTO_AES_KEYEXPANDER_H
#define CRYPTO_AES_KEYEXPANDER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/types.h"
#include "Crypto/aes_helper.h"
#include <string>

namespace Crypto {

  namespace AES {
    
    class KeyExpander
    {
    private:
      Helper m_helper;

      inline void schedule_core(std::string& cipher, uint i);

    public:
      KeyExpander();

      inline number_size_t expanded_length(number_size_t key_length);

      inline number_size_t rounds(number_size_t key_length);

      std::string expand(const std::string& key);

    };
    
  } // namespace AES

} // namespace Crypto

#endif // CRYPTO_AES_KEYEXPANDER_H
