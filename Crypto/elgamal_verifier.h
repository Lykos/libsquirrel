#ifndef CRYPTO_ELGAMAL_VERIFIER_H
#define CRYPTO_ELGAMAL_VERIFIER_H

#include "Crypto/elgamal_types.h"
#include "Crypto/longintconverter.h"
#include "Crypto/sha2hasher.h"
#include <string>

namespace Crypto {

  namespace Elgamal {
    
    class Verifier
    {
    public:
      explicit Verifier(const public_key_t& public_key);

      Verifier(const std::string& raw_public_key);

      bool verify(const number_t& message, const number_t& r, const number_t& s) const;

      // Assumes that the signature is directly before the end of the message.
      bool verify(const std::string& message) const;

      number_size_t signature_length() const { return m_signature_length; }

    private:
      number_t m_modulus, m_generator, m_gen_power;

      number_size_t m_r_length, m_s_length, m_signature_length;

      LongIntConverter m_converter;

      SHA2Hasher hasher;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
