#ifndef CRYPTO_ELGAMAL_VERIFIER_H
#define CRYPTO_ELGAMAL_VERIFIER_H

#include "elgamal_types.h"
#include "DataStructures/longintconverter.h"
#include "sha2hasher.h"
#include "preconditionviolation.h"
#include <string>

namespace Crypto {

  namespace Elgamal {
    
    class Verifier
    {
    public:
      explicit Verifier(const public_key_t& public_key);

      Verifier(const std::string& raw_public_key);

      bool verify(const number_t& message, const number_t& r, const number_t& s) const;

      // Assumes that the signature is directly before the end of the message and removes it.
      bool verify(const std::string& message) const;

      number_size_t signature_length() const { return m_signature_length; }

      std::string& remove_signature(std::string& message) const;

    private:
      number_t m_modulus, m_generator, m_gen_power;

      number_size_t m_r_length, m_s_length, m_signature_length;

      DataStructures::LongIntConverter m_converter;

      SHA2Hasher m_hasher;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
