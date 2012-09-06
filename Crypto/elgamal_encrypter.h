#ifndef CRYPTO_ELGAMAL_ENCRYPTER_H
#define CRYPTO_ELGAMAL_ENCRYPTER_H

#include "types.h"
#include "elgamal_types.h"
#include "DataStructures/uniformlongintdistribution.h"
#include "DataStructures/longintconverter.h"
#include <boost/random/random_device.hpp>

namespace Crypto {

  namespace Elgamal {
    
    class Encrypter
    {
    public:
      typedef struct {
        number_t cipher;
        number_t gen_power;
      } cipher_t;

      explicit Encrypter(const public_key_t& public_key);

      // We have to reimplement them all because random_device is not copyable
      Encrypter(const Encrypter& other);

      Encrypter(Encrypter&& other);

      Encrypter& operator=(const Encrypter& other);

      Encrypter& operator=(Encrypter&& other);

      ~Encrypter();

      Encrypter(const std::string& raw_public_key);

      cipher_t encrypt(const number_t& plain);

      std::string encrypt(const std::string& plain);

      number_size_t plain_block_size() const { return m_plain_length; }

      number_size_t cipher_block_size() const { return m_cipher_length; }

    private:
      number_t m_modulus, m_generator, m_gen_power;

      DataStructures::UniformLongIntDistribution m_exponent_distribution;

      boost::random::random_device m_random_generator;

      // cipher_part_length is the length of the encrypted text itself, cipher_length also includes
      // the key part, which also has to be sent
      number_size_t m_plain_length, m_key_part_length, m_cipher_part_length, m_cipher_length;

      DataStructures::LongIntConverter m_converter;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_ENCRYPTER_H
