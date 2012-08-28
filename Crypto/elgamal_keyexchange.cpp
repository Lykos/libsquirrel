#include "elgamal_keyexchange.h"
#include "elgamal_constants.h"

namespace Crypto {

  namespace Elgamal {

    group_t KeyExchange::choose_group(uint number_bits)
    {
      number_t modulus, generator;
      if (number_bits == 1024) {
        modulus = diffie_hellman_modulus_1024;
        generator = diffie_hellman_generator_1024;
      } else if (number_bits == 2048) {
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
      return {modulus, generator};
    }

    number_t KeyExchange::complete(const number_t& gen_power, const exponent_t& own_exponent, const group_t& group)
    {
      return gen_power.pow_mod(own_exponent, group.modulus);
    }

  } // namespace Elgamal

} // namespace Crypto
