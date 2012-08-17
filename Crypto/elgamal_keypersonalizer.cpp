#include "elgamal_keypersonalizer.h"

namespace Crypto {

  namespace Elgamal {

    personalized_public_key_t KeyPersonalizer::personalize_key(public_key_t public_key) const
    {
      const number_t& modulus = public_key.modulus;
      const number_t& generator = public_key.generator;
      const number_t& public_gen_power = public_key.gen_power;
      exponent_t exponent = rand_number(modulus - 1);
      number_t gen_power = generator.pow_mod(exponent, modulus);
      number_t key = public_gen_power.pow_mod(exponent, modulus);
      number_t key_inv = key.inv_mod(modulus);
      return {modulus, gen_power, key_inv};
    }

    
  } // namespace Elgamal

} // namespace Crypto
