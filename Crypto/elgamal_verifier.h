#ifndef CRYPTO_ELGAMAL_VERIFIER_H
#define CRYPTO_ELGAMAL_VERIFIER_H

#include "elgamal_types.h"
#include "longintconverter.h"
#include "sha256hasher.h"

namespace Crypto {

  namespace Elgamal {
    
    class Verifier
    {
    private:
      number_t m_modulus, m_generator, m_gen_power;

      uint m_r_length, m_s_length, m_signature_length;

      LongIntConverter m_converter;

      SHA256Hasher hasher;

    public:
      Verifier(const public_key_t& public_key);

      // Assumes that the signature is directly before the end of the message.
      bool verify(const elgamal_byte_t* message, ulong length);

      uint signature_length() const { return m_signature_length; }

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
