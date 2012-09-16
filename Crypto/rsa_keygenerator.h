#ifndef CRYPTO_RSA_KEYGENERATOR_H
#define CRYPTO_RSA_KEYGENERATOR_H

#include "rsa_types.h"
#include "primetester.h"
#include "LongArithmetic/uniformlongintdistribution.h"
#include "LongArithmetic/algebrahelper.h"

namespace Crypto {

  namespace RSA {

    class KeyGenerator
    {
    public:
      inline explicit KeyGenerator(PrimeTester prime_tester = PrimeTester()): m_prime_tester (prime_tester) {}

      // Totally insecure, uses all types of insecure p,q pairs.
      template <typename Engine>
      key_pair_t generate(Engine& engine, number_size_t number_bits);

    private:
      PrimeTester m_prime_tester;

    };

    template <typename Engine>
    key_pair_t KeyGenerator::generate(Engine& engine, number_size_t number_bits)
    {
      static const number_t ONE = 1;
      LongArithmetic::LongInt min = ++(ONE << (number_bits - 1));
      LongArithmetic::LongInt max = --(ONE << number_bits);
      number_t p = m_prime_tester.random_prime(engine, min, max, std::max(number_size_t(20), number_bits + 10));
      number_t q;
      do {
        q = m_prime_tester.random_prime(engine, min, max, std::max(number_size_t(20), number_bits + 10));
      } while (p == q);
      number_t modulus = p * q;
      number_t phi_n = (p - ONE) * (q - ONE);
      exponent_t e;
      do {
        LongArithmetic::UniformLongIntDistribution dist (0, phi_n - ONE);
        e = dist(engine);
      } while (LongArithmetic::AlgebraHelper::gcd(phi_n, e) != ONE);
      exponent_t d = e.mult_inv_mod(phi_n);
      private_key_t private_key {modulus, e, p, q, true};
      public_key_t public_key {modulus, d};
      return {public_key, private_key};
    }

  }

}

#endif // CRYPTO_RSA_KEYGENERATOR_H
