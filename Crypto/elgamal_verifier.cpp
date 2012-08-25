#include "elgamal_verifier.h"

namespace Crypto {

  namespace Elgamal {
    
    bool Verifier::verify(plain_text_t plain_text, signature_t signature)
    {
      return m_public_key.generator.pow_mod(plain_text, m_public_key.modulus)
          == (m_public_key.gen_power.pow_mod(signature.r, m_public_key.modulus)
              * signature.r.pow_mod(signature.s, m_public_key.modulus)).mod(m_public_key.modulus);
    }
    


  } // namespace Elgamal

} // namespace Crypto
