#ifndef CRYPTO_RSA_KEYGENERATOR_H
#define CRYPTO_RSA_KEYGENERATOR_H

#include "Crypto_global.h"
#include "rsa_types.h"
#include "primetester.h"
#include "uniformlongintdistribution.h"
#include "arithmetichelper.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT KeyGenerator
    {
    public:
      inline explicit KeyGenerator(PrimeTester prime_tester = PrimeTester()): m_prime_tester (prime_tester) {}

      // Totally insecure, uses all types of insecure p,q pairs.
      template <typename Engine>
      key_pair_t generate(Engine& engine, uint number_bits);

    private:
      PrimeTester m_prime_tester;

    };

    template <typename Engine>
    key_pair_t KeyGenerator::generate(Engine& engine, uint number_bits)
    {
      static const number_t ONE = 1;
      DataStructures::LongInt min = ++(ONE << (number_bits - 1));
      DataStructures::LongInt max = --(ONE << number_bits);
      number_t p = m_prime_tester.random_prime(engine, min, max, std::max(20u, number_bits + 10));
      number_t q;
      do {
        q = m_prime_tester.random_prime(engine, min, max, std::max(20u, number_bits + 10));
      } while (p == q);
      number_t modulus = p * q;
      number_t phi_n = (p - ONE) * (q - ONE);
      exponent_t e;
      do {
        DataStructures::UniformLongIntDistribution dist (0, phi_n - ONE);
        e = dist(engine);
      } while (DataStructures::ArithmeticHelper::gcd(phi_n, e) != ONE);
      exponent_t d = e.mult_inv_mod(phi_n);
      private_key_t private_key {modulus, e, p, q, true};
      public_key_t public_key {modulus, d};
      return {public_key, private_key};
    }

  }

}

#endif // CRYPTO_RSA_KEYGENERATOR_H
