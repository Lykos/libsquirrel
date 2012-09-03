#ifndef CRYPTO_ELGAMAL_KEYGENERATOR_H
#define CRYPTO_ELGAMAL_KEYGENERATOR_H

#include "Crypto_global.h"
#include "primetester.h"
#include "elgamal_types.h"
#include "dh_keygenerator.h"
#include "elgamal_converter.h"

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyGenerator : private DH::KeyGenerator
    {
    public:
      typedef KeyPair<std::string, std::string> raw_key_pair_t;

      template <typename Engine>
      inline raw_key_pair_t generate_raw(Engine& engine, uint number_bits);

      template <typename Engine>
      inline key_pair_t generate(Engine& engine, uint number_bits);

      template <typename Engine>
      inline key_pair_t generate(Engine& engine, const group_t& group);

      group_t choose_group(uint number_bits);

      number_size_t max_public_length(uint number_bits) const throw() { return 3 * number_bits; }

      number_size_t max_private_length(uint number_bits) const throw() { return 3 * number_bits; }

    private:
      Converter m_converter;

    };

    template <typename Engine>
    inline KeyGenerator::raw_key_pair_t KeyGenerator::generate_raw(Engine& engine, uint number_bits)
    {
      key_pair_t key_pair = generate(engine, number_bits);
      return {m_converter.write_public_key(key_pair.public_key), m_converter.write_private_key(key_pair.private_key)};
    }

    template <typename Engine>
    inline key_pair_t KeyGenerator::generate(Engine& engine, uint number_bits)
    {
      return generate(engine, choose_group(number_bits));
    }

    template <typename Engine>
    inline key_pair_t KeyGenerator::generate(Engine& engine, const group_t& group)
    {
      DH::partial_key_pair_t partial_key = DH::KeyGenerator::generate(engine, group);
      public_key_t public_key {group.modulus, group.generator, partial_key.gen_power};
      private_key_t private_key {group.modulus, group.generator, partial_key.exponent};
      return {public_key, private_key};
    }

  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYGENERATOR_H
