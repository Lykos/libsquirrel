#ifndef CRYPTO_ELGAMAL_ENCRYPTER_H
#define CRYPTO_ELGAMAL_ENCRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"
#include "encrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Encrypter : public Crypto::Encrypter<public_key_t, plain_text_t, cipher_text_t>
    {
    private:
      typedef Crypto::Encrypter<public_key_t, plain_text_t, cipher_text_t> CryptoEncrypter;

    public:
      inline Encrypter(const public_key_t& public_key): CryptoEncrypter (public_key) {}

      cipher_text_t encrypt(const plain_text_t& plain_text);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_ENCRYPTER_H
