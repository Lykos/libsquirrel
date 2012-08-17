#include "rsa_keygenerator.h"

namespace Crypto {

  namespace RSA {

    key_pair_t KeyGenerator::generate(DataStructures::index_type number_bits) const {
      number_t p = m_prime_tester.random_prime(number_bits);
      number_t q;
      do {
        q = m_prime_tester.random_prime(number_bits);
      } while (p == q);
      number_t modulus = p * q;
      number_t phi_n = (p - 1) * (q - 1);
      exponent_t e;
      do {
        e = rand_number(phi_n);
      } while (gcd(phi_n, e) != 1);
      exponent_t d = e.inv_mod(phi_n);
      private_key_t private_key {modulus, e, p, q, true};
      public_key_t public_key {modulus, d};
      return {public_key, private_key};
    }
  }

}
