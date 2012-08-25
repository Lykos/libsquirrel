#ifndef CRYPTO_RSA_KEYGENERATOR_H
#define CRYPTO_RSA_KEYGENERATOR_H

#include "Crypto_global.h"
#include "rsa_types.h"
#include "primetester.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT KeyGenerator
    {
    public:
      inline explicit KeyGenerator(PrimeTester prime_tester = PrimeTester()): m_prime_tester (prime_tester) {}

      key_pair_t generate(DataStructures::index_type number_bits);

    private:
      PrimeTester m_prime_tester;

    };

  }

}

#endif // CRYPTO_RSA_KEYGENERATOR_H
