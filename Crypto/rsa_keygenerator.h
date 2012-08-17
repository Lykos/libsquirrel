#ifndef CRYPTO_RSA_KEYGENERATOR_H
#define CRYPTO_RSA_KEYGENERATOR_H

#include "Crypto_global.h"
#include "keygenerator.h"
#include "rsa_types.h"
#include "primetester.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT KeyGenerator : public Crypto::KeyGenerator<key_pair_t>
    {
    public:
      inline explicit KeyGenerator(PrimeTester prime_tester = PrimeTester()): m_prime_tester (prime_tester) {}

      inline KeyGenerator(const KeyGenerator& other): m_prime_tester (other.m_prime_tester) {}

      inline KeyGenerator& operator=(const KeyGenerator& other) { m_prime_tester = other.m_prime_tester; return *this; }

      key_pair_t generate(DataStructures::index_type number_bits) const;

    private:
      PrimeTester m_prime_tester;

    };

  }

}

#endif // CRYPTO_RSA_KEYGENERATOR_H
