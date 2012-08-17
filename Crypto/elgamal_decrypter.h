#ifndef CRYPTO_ELGAMAL_DECRYPTER_H
#define CRYPTO_ELGAMAL_DECRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"
#include "decrypter.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Decrypter : public Crypto::Decrypter<private_key_t, plain_text_t, cipher_text_t>
    {
    private:
      typedef Crypto::Decrypter<private_key_t, plain_text_t, cipher_text_t> CryptoDecrypter;

    public:
      inline explicit Decrypter(const private_key_t& private_key): CryptoDecrypter(private_key) {}

      inline Decrypter(const Decrypter& other): CryptoDecrypter(other) {}

      inline Decrypter& operator=(const Decrypter& other) { CryptoDecrypter::operator=(other); return *this; }

      plain_text_t decrypt(const cipher_text_t &cipher_text) const;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_DECRYPTER_H
