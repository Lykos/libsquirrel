#ifndef CRYPTO_ELGAMAL_KEYEXCHANGE_H
#define CRYPTO_ELGAMAL_KEYEXCHANGE_H

#include "elgamal_types.h"

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyExchange
    {
    public:

      group_t choose_group(uint number_bits);

      template <typename Engine>
      partial_key_t generate(Engine& engine, const group_t& group);

      number_t complete(const number_t& gen_power, const exponent_t& own_exponent, const group_t& group);

    };

    template <typename Engine>
    partial_key_t KeyExchange::generate(Engine& engine, const group_t& group)
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

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYEXCHANGE_H
