#include "elgamal_verifier.h"

namespace Crypto {

  namespace Elgamal {
    
    Verifier::Verifier(const public_key_t& public_key):
      m_modulus (public_key.modulus),
      m_generator (public_key.generator),
      m_gen_power (public_key.gen_power),
      m_r_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_s_length (m_modulus.size() * sizeof(number_t::part_type))
    {}

    bool Verifier::verify(const elgamal_byte_t* plain_text, uint length, const elgamal_byte_t* signature)
    {
      elgamal_byte_t hash[32];
      hasher.hash(plain_text, length, hash);
      number_t hash_number = m_converter.convert(hash, 32);
      number_t r = m_converter.convert(signature, m_r_length);
      number_t s = m_converter.convert(signature, m_s_length);
      return m_generator.pow_mod(hash_number, m_modulus)
          == (m_gen_power.pow_mod(r, m_modulus) * r.pow_mod(s, m_modulus)).mod(m_modulus);
    }

  } // namespace Elgamal

} // namespace Crypto
