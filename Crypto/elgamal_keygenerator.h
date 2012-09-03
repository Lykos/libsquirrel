#ifndef CRYPTO_ELGAMAL_KEYGENERATOR_H
#define CRYPTO_ELGAMAL_KEYGENERATOR_H

#include "Crypto/Crypto_global.h"
#include "Crypto/primetester.h"
#include "Crypto/elgamal_types.h"
#include "Crypto/dh_keygenerator.h"
#include "Crypto/elgamal_converter.h"

namespace Crypto {

  namespace Elgamal {

    class CRYPTOSHARED_EXPORT KeyGenerator : private DH::KeyGenerator
    {
    public:
      template <typename Engine>
      inline std::pair<number_size_t, number_size_t>
      generate(Engine& engine, uint number_bits, byte_t* public_key, byte_t* private_key);

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
    inline std::pair<number_size_t, number_size_t>
    KeyGenerator::generate(Engine& engine, uint number_bits, byte_t* raw_public_key, byte_t* raw_private_key)
    {
      key_pair_t key_pair = generate(engine, number_bits);
      number_size_t public_length = m_converter.write_public_key(key_pair.public_key, raw_public_key);
      number_size_t private_length = m_converter.write_private_key(key_pair.private_key, raw_private_key);
      return std::make_pair(public_length, private_length);
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
