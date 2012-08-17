#include "elgamal_keygenerator.h"

namespace Crypto {

  namespace Elgamal {
    
    key_pair_t KeyGenerator::generate(DataStructures::index_type number_bits) const
    {
      number_t modulus;
      number_t p;
      do {
        p = m_prime_tester.random_prime(number_bits - 1);
        modulus = (p << 1) + 1;
      } while (!m_prime_tester.is_prime(modulus));
      number_t generator;
      number_t minus_one = modulus - 1;
      do {
        generator = rand_number(minus_one); // Excludes -1 itself, which would pass the next test.
      } while (generator.pow_mod(p, modulus) != minus_one);
      exponent_t exponent = rand_number(modulus - 1);
      number_t gen_power = generator.pow_mod(exponent, modulus);
      public_key_t public_key {modulus, generator, gen_power};
      private_key_t private_key {modulus, generator, exponent};
      return {public_key, private_key};
    }
    
  } // namespace Elgamal

} // namespace Crypto
