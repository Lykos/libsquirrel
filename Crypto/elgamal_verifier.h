#ifndef CRYPTO_ELGAMAL_VERIFIER_H
#define CRYPTO_ELGAMAL_VERIFIER_H

#include "elgamal_types.h"
#include "longintconverter.h"
#include "sha2hasher.h"
#include "preconditionviolation.h"
#include <string>

namespace Crypto {

  namespace Elgamal {
    
    class Verifier
    {
    public:
      explicit Verifier(const public_key_t& public_key) throw(PreconditionViolation);

      Verifier(const std::string& raw_public_key) throw(PreconditionViolation);

      bool verify(const number_t& message, const number_t& r, const number_t& s) const throw();

      // Assumes that the signature is directly before the end of the message and removes it.
      bool verify(const std::string& message) const throw();

      number_size_t signature_length() const throw() { return m_signature_length; }

      std::string& remove_signature(std::string& message) const throw(PreconditionViolation);

    private:
      number_t m_modulus, m_generator, m_gen_power;

      number_size_t m_r_length, m_s_length, m_signature_length;

      LongIntConverter m_converter;

      SHA2Hasher m_hasher;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
