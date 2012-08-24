#include "aes_encrypter.h"
#include "aes_keyexpander.h"

namespace Crypto {

  namespace AES {

    Encryter::Encrypter(const key_t& key): CryptoEncrypter(key)
    {
      KeyExpander expander;
      expander.expand(m_key, m_expanded_key);
    }

  }

}
