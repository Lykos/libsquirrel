#ifndef CRYPTO_ELGAMAL_ENCRYPTER_H
#define CRYPTO_ELGAMAL_ENCRYPTER_H

#include "Crypto_global.h"
#include "elgamal_keypersonalizer.h"
#include "elgamal_types.h"
#include "encrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Encrypter : public Crypto::Encrypter<personalized_public_key_t, plain_text_t, cipher_text_t>
    {
    private:
      typedef Crypto::Encrypter<personalized_public_key_t, plain_text_t, cipher_text_t> CryptoEncrypter;

    public:
      inline Encrypter(const public_key_t& public_key, const Crypto::KeyPersonalizer<public_key_t, personalized_public_key_t>& personalizer = Crypto::Elgamal::KeyPersonalizer()):
        CryptoEncrypter (personalizer.personalize_key(public_key))
      {}

      inline Encrypter(const personalized_public_key_t& personalized_public_key): CryptoEncrypter (personalized_public_key) {}

      inline Encrypter(const Encrypter& other): CryptoEncrypter(other) {}

      inline Encrypter& operator=(const Encrypter& other) { CryptoEncrypter::operator=(other); return *this; }

      cipher_text_t encrypt(const plain_text_t& plain_text) const;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_ENCRYPTER_H
