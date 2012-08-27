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

      uint m_r_length, m_s_length;

      LongIntConverter m_converter;

      SHA256Hasher hasher;

    public:
      Verifier(const public_key_t& public_key);

      bool verify(const elgamal_byte_t* plain_text, uint length, const elgamal_byte_t* signature);

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_VERIFIER_H
