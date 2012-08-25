#ifndef CRYPTO_ELGAMAL_SIGNER_H
#define CRYPTO_ELGAMAL_SIGNER_H

#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {
    
    class Signer
    {
    private:
      private_key_t m_private_key;

    public:
      Signer(private_key_t private_key): m_private_key (private_key) {}

      signature_t sign(plain_text_t plain_text);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_SIGNER_H
