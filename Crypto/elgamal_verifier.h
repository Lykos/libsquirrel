#ifndef CRYPTO_ELGAMAL_VERIFIER_H
#define CRYPTO_ELGAMAL_VERIFIER_H

#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {
    
    class Verifier
    {
    private:
      public_key_t m_public_key;

    public:
      Verifier(public_key_t public_key): m_public_key (public_key) {}

      bool verify(plain_text_t plain_text, signature_t signature);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
