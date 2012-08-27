#ifndef CRYPTO_ELGAMAL_KEYGENERATOR_H
#define CRYPTO_ELGAMAL_KEYGENERATOR_H

#include "Crypto_global.h"
#include "primetester.h"
#include "elgamal_types.h"
#include "elgamal_constants.h"
#include <iostream>

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyGenerator
    {
    public:
      template <typename Engine>
      key_pair_t generate(Engine& engine, uint number_bits);

    };

    template <typename Engine>
    key_pair_t KeyGenerator::generate(Engine& engine, uint number_bits)
    {
      static const number_t ZERO = 0;
      static const number_t ONE = 1;
      number_t modulus, generator;
      if (number_bits == 2048) {
        modulus = diffie_hellman_modulus_2048_1;
        generator = diffie_hellman_generator_2048_1;
      } else if (number_bits == 2560) {
        modulus = diffie_hellman_modulus_2560;
        generator = diffie_hellman_generator_2560;
      } else if (number_bits == 3072) {
        modulus = diffie_hellman_modulus_3072;
        generator = diffie_hellman_generator_3072;
      } else if (number_bits == 3584) {
        modulus = diffie_hellman_modulus_3584;
        generator = diffie_hellman_generator_3584;
      } else if (number_bits == 4096) {
        modulus = diffie_hellman_modulus_4096;
        generator = diffie_hellman_generator_4096;
      } else if (number_bits == 8192) {
        modulus = diffie_hellman_modulus_8192;
        generator = diffie_hellman_generator_8192;
      } else {
        throw std::logic_error("Unsupported key length");
      }
      number_t p = modulus >> 1;
      DataStructures::UniformLongIntDistribution e_dist (ZERO, p - ONE);
      exponent_t exponent = e_dist(engine);
      number_t gen_power = generator.pow_mod(exponent, modulus);
      public_key_t public_key {modulus, generator, gen_power};
      private_key_t private_key {modulus, generator, exponent};
      return {public_key, private_key};
    }

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYGENERATOR_H
