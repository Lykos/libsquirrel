#ifndef CRYPTO_ELGAMAL_KEYGENERATOR_H
#define CRYPTO_ELGAMAL_KEYGENERATOR_H

#include "Crypto/Crypto_global.h"
#include "Crypto/primetester.h"
#include "Crypto/elgamal_types.h"
#include "Crypto/dh_keygenerator.h"

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyGenerator : private DH::KeyGenerator
    {
    public:
      template <typename Engine>
      key_pair_t generate(Engine& engine, uint number_bits);

      template <typename Engine>
      key_pair_t generate(Engine& engine, const group_t& group);

      group_t choose_group(uint number_bits);

    };

    template <typename Engine>
    key_pair_t KeyGenerator::generate(Engine& engine, uint number_bits)
    {
      return generate(engine, choose_group(number_bits));
    }

    template <typename Engine>
    key_pair_t KeyGenerator::generate(Engine& engine, const group_t& group)
    {
      DH::partial_key_pair_t partial_key = DH::KeyGenerator::generate(engine, group);
      public_key_t public_key {group.modulus, group.generator, partial_key.gen_power};
      private_key_t private_key {group.modulus, group.generator, partial_key.exponent};
      return {public_key, private_key};
    }

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYGENERATOR_H
