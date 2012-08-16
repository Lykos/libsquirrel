#ifndef RSA_H
#define RSA_H

#include "rsa_types.h"
#include "rsa_decryptstrategy.h"
#include "decrypter.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT Decrypter : public Crypto::Decrypter<private_key_t, plain_text_t, cipher_text_t>
    {
    private:
      typedef Crypto::Decrypter<private_key_t, plain_text_t, cipher_text_t> CryptoDecrypter;

    public:
      Decrypter(const private_key_t& private_key);

      inline Decrypter(const Decrypter& other): CryptoDecrypter(other), m_strategy(other.m_strategy->copy()) {}

      Decrypter& operator=(const Decrypter& other);

      inline plain_text_t decrypt(const cipher_text_t& cipher_text) { return m_strategy->decrypt(cipher_text); }

      inline virtual ~Decrypter() { delete m_strategy; }

    private:
      DecryptStrategy *m_strategy;

    };

  }

}

#endif // RSA_H
