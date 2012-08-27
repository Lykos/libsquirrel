#include "elgamal_signer.h"
#include "elgamal_types.h"
#include "arithmetichelper.h"
#include "longint.h"

namespace Crypto {

  namespace Elgamal {

    using namespace DataStructures::ArithmeticHelper;

    static const number_t ZERO = 0;

    static const number_t ONE = 1;

    Signer::Signer(const private_key_t& private_key):
      m_modulus (private_key.modulus),
      m_generator (private_key.generator),
      m_phi_modulus (m_modulus - ONE),
      m_exponent (private_key.exponent),
      m_k_distribution (ONE, m_phi_modulus - ONE),
      m_r_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_s_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_signature_length (m_r_length + m_s_length)
    {}

    void Signer::sign(const elgamal_byte_t* plain_text, uint length, elgamal_byte_t* signature)
    {
      elgamal_byte_t hash[32];
      hasher.hash(plain_text, length, hash + 0);
      number_t hash_number = m_converter.convert(hash, 32);
      number_t r, s;
      do {
        number_t k;
        do {
          k = m_k_distribution(m_random_generator);
        } while (gcd(k, m_phi_modulus) != ONE);
        r = m_generator.pow_mod(k, m_modulus);
        number_t k_inv = k.mult_inv_mod(m_modulus);
        s = ((hash_number - m_exponent * r) * k_inv).mod(m_modulus);
      } while (s == ZERO);
      m_converter.convert(r, signature, m_r_length);
      m_converter.convert(s, signature + m_r_length, m_s_length);
    }
    
  } // namespace Elgamal

} // namespace Crypto
