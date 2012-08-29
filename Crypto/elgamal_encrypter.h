#ifndef CRYPTO_ELGAMAL_ENCRYPTER_H
#define CRYPTO_ELGAMAL_ENCRYPTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/elgamal_types.h"
#include "DataStructures/uniformlongintdistribution.h"
#include "Crypto/longintconverter.h"
#include <boost/random/random_device.hpp>

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Encrypter
    {
    public:
      typedef LongIntConverter::number_size_t number_size_t;

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

      Encrypter(const elgamal_byte_t* raw_public_key, number_size_t length);

      cipher_t encrypt(const number_t& plain);

      void encrypt(const elgamal_byte_t* plain, elgamal_byte_t* cipher);

      number_size_t plain_block_size() const { return m_plain_length; }

      number_size_t cipher_block_size() const { return m_cipher_length; }

    private:
      number_t m_modulus, m_generator, m_gen_power;

      DataStructures::UniformLongIntDistribution m_exponent_distribution;

      std::random_device m_random_generator;

      number_size_t m_plain_length, m_key_part_length, m_cipher_length;

      LongIntConverter m_converter;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_ENCRYPTER_H
