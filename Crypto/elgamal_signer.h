#ifndef CRYPTO_ELGAMAL_SIGNER_H
#define CRYPTO_ELGAMAL_SIGNER_H

#include "types.h"
#include "elgamal_types.h"
#include "DataStructures/uniformlongintdistribution.h"
#include "longintconverter.h"
#include "sha2hasher.h"
#include <boost/random/random_device.hpp>

namespace Crypto {

  namespace Elgamal {
    
    class Signer
    {
    public:
      typedef struct {
        number_t r;
        number_t s;
      } signature_t;

      explicit Signer(const private_key_t& private_key);

      Signer(const std::string& raw_private_key);


      // We have to reimplement them all because random_device is not copyable
      Signer(const Signer& other);

      Signer(Signer&& other);

      Signer& operator=(const Signer& other);

      Signer& operator=(Signer&& other);

      ~Signer();

      signature_t sign(const number_t& message);

      // Appends the signature directly after the end of the message
      void sign(std::string& message);

      number_size_t signature_length() const { return m_signature_length; }

    private:
      number_t m_modulus, m_generator, m_phi_modulus;

      exponent_t m_exponent;

      boost::random::random_device m_random_generator;

      DataStructures::UniformLongIntDistribution m_k_distribution;

      number_size_t m_r_length, m_s_length, m_signature_length;

      LongIntConverter m_converter;

      SHA2Hasher hasher;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_SIGNER_H
