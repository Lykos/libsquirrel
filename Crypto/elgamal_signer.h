#ifndef CRYPTO_ELGAMAL_SIGNER_H
#define CRYPTO_ELGAMAL_SIGNER_H

#include "elgamal_types.h"
#include "uniformlongintdistribution.h"
#include "longintconverter.h"
#include "sha256hasher.h"
#include <boost/random/random_device.hpp>

namespace Crypto {

  namespace Elgamal {
    
    class Signer
    {
    private:
      number_t m_modulus, m_generator, m_phi_modulus;

      exponent_t m_exponent;

      std::random_device m_random_generator;

      DataStructures::UniformLongIntDistribution m_k_distribution;

      uint m_r_length, m_s_length, m_signature_length;

      LongIntConverter m_converter;

      SHA256Hasher hasher;

    public:
      explicit Signer(const private_key_t& private_key);

      void sign(const elgamal_byte_t* plain_text, uint length, elgamal_byte_t* signature);

      uint signature_length() const { return m_signature_length; }

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_SIGNER_H
