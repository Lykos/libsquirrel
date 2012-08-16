#include "rsa_keygenerator.h"

namespace Crypto {

  namespace RSA {

    key_pair_t KeyGenerator::generate() const {
      number_t p = 7;
      number_t q = 71;
      number_t modulus = p * q;
      number_t phi_n = (p - 1) * (q - 1);
      exponent_t e;
      do {
        rand_number(phi_n);
      } while (gcd(phi_n, e) != 1);
      exponent_t d = e.inv_mod(phi_n);
      private_key_t private_key {modulus, e, p, q, true};
      public_key_t public_key {modulus, e};
      return std::make_pair(public_key, private_key);
    }
  }

}
