#include "dh_keygenerator.h"
#include "dh_constants.h"
#include "preconditionviolation.h"

namespace Crypto {

  namespace DH {

    bool KeyGenerator::valid_key_bits(number_size_t number_bits) const
    {
      return number_bits == 512
          || number_bits == 1024
          || number_bits == 2048
          || number_bits == 2560
          || number_bits == 3072
          || number_bits == 3584
          || number_bits == 4096
          || number_bits == 8192;
    }

    group_t KeyGenerator::choose_group(number_size_t number_bits)
    {
      PREC(ElgamalKeyLength, valid_key_bits(number_bits));
      number_t modulus, generator;
      // TODO Do this automatically.
      if (number_bits == 512) {
        modulus = diffie_hellman_modulus_512;
        generator = diffie_hellman_generator_512;
      } else if (number_bits == 1024) {
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
      }
      return {modulus, generator};
    }

  } // namespace Elgamal

} // namespace Crypto
