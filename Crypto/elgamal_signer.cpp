#include "elgamal_signer.h"
#include "elgamal_types.h"
#include "arithmetichelper.h"
#include "longint.h"

namespace Crypto {

  namespace Elgamal {
    
    signature_t Signer::sign(plain_text_t plain_text)
    {
      using namespace DataStructures;
      using namespace ArithmeticHelper;
      LongInt r, s;
      do {
        LongInt k;
        LongInt phi_p = m_private_key.modulus - 1;
        do {
          k = rand_number(m_private_key.modulus - 2) + 1;
        } while (gcd(k, phi_p) == 1);
        r = m_private_key.generator.pow_mod(k, m_private_key.modulus);
        LongInt k_inv = k.mult_inv_mod(m_private_key.modulus);
        s = ((plain_text - m_private_key.exponent * r) * k_inv).mod(m_private_key.modulus);
      } while (s == 0);
      return {r, s};
    }
    
  } // namespace Elgamal

} // namespace Crypto
