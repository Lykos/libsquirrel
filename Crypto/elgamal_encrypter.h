#ifndef CRYPTO_ELGAMAL_ENCRYPTER_H
#define CRYPTO_ELGAMAL_ENCRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"
#include "uniformlongintdistribution.h"
#include "longintconverter.h"
#include <boost/random/random_device.hpp>

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Encrypter
    {
    private:
      number_t m_modulus, m_generator, m_gen_power;

      DataStructures::UniformLongIntDistribution m_exponent_distribution;

      std::random_device m_random_generator;

      uint m_plain_length, m_exponent_length, m_cipher_length;

      LongIntConverter m_converter;

    public:
      explicit Encrypter(const public_key_t& public_key);

      void encrypt(const elgamal_byte_t* plain, elgamal_byte_t* cipher);

      uint plain_block_size() const { return m_plain_length; }

      uint cipher_block_size() const { return m_cipher_length; }

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_ENCRYPTER_H
