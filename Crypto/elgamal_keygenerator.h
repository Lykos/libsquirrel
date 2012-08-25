#ifndef CRYPTO_ELGAMAL_KEYGENERATOR_H
#define CRYPTO_ELGAMAL_KEYGENERATOR_H

#include "Crypto_global.h"
#include "primetester.h"
#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyGenerator
    {
    public:
      inline explicit KeyGenerator(PrimeTester prime_tester = PrimeTester()): m_prime_tester (prime_tester) {}

      key_pair_t generate(DataStructures::index_type number_bits) const;

    private:
      PrimeTester m_prime_tester;

    };

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYGENERATOR_H
