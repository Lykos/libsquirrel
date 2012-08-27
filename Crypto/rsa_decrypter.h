#ifndef CRYPTO_RSA_DECRYPTER_H
#define CRYPTO_RSA_DECRYPTER_H

#include "rsa_types.h"
#include "rsa_decryptstrategy.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT Decrypter
    {
    public:
      explicit Decrypter(const private_key_t& private_key);

      Decrypter(const Decrypter& other);

      Decrypter(Decrypter&& other);

      Decrypter& operator=(Decrypter&& other);

      Decrypter& operator=(const Decrypter& other);

      inline plain_text_t decrypt(const cipher_text_t& cipher_text) { return m_strategy->decrypt(cipher_text); }

      inline virtual ~Decrypter() { delete m_strategy; }

    private:
      private_key_t m_private_key;

      DecryptStrategy *m_strategy;

    };

  } // namespace RSA

} // namespace Crypto

#endif // CRYPTO_RSA_DECRYPTER_H
