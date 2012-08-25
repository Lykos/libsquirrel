#ifndef CRYPTO_ELGAMAL_DECRYPTER_H
#define CRYPTO_ELGAMAL_DECRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    private:
      private_key_t m_private_key;

    public:
      inline explicit Decrypter(const private_key_t& private_key): m_private_key (private_key) {}

      plain_text_t decrypt(const cipher_text_t &cipher_text);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_DECRYPTER_H
