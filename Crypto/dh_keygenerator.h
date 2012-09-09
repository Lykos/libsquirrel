#ifndef CRYPTO_DH_KEYGENERATOR_H
#define CRYPTO_DH_KEYGENERATOR_H

#include "DataStructures/uniformlongintdistribution.h"
#include "dh_types.h"

namespace Crypto {

  namespace DH {

    class KeyGenerator
    {
    public:
      bool valid_key_bits(number_size_t number_bits) const;

      group_t choose_group(number_size_t number_bits);

      template <typename Engine>
      partial_key_pair_t generate(Engine& engine, const group_t& group);

    };

    template <typename Engine>
    partial_key_pair_t KeyGenerator::generate(Engine& engine, const group_t& group)
    {
      static const number_t ZERO = 0;
      static const number_t ONE = 1;
      const number_t& modulus = group.modulus;
      const number_t& generator = group.generator;
      number_t p = modulus >> 1;
      DataStructures::UniformLongIntDistribution e_dist (ZERO, p - ONE);
      exponent_t exponent = e_dist(engine);
      number_t gen_power = generator.pow_mod(exponent, modulus);
      return {gen_power, exponent};
    }

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_KEYGENERATOR_H
