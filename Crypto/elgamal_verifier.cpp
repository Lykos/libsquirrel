#include "elgamal_verifier.h"
#include "elgamal_converter.h"
#include <string>

using namespace std;

namespace Crypto {

  namespace Elgamal {
    
    Verifier::Verifier(const public_key_t& public_key):
      m_modulus (public_key.modulus),
      m_generator (public_key.generator),
      m_gen_power (public_key.gen_power),
      m_r_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_s_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_signature_length (m_r_length + m_s_length)
    {}

    Verifier::Verifier(const std::string& raw_public_key)
    {
      Converter conv;
      public_key_t public_key = conv.read_public_key(raw_public_key);
      m_modulus = public_key.modulus;
      m_generator = public_key.generator;
      m_gen_power = public_key.gen_power;
      m_r_length = m_modulus.size() * sizeof(number_t::part_type);
      m_s_length = m_modulus.size() * sizeof(number_t::part_type);
      m_signature_length = m_r_length + m_s_length;
    }

    bool Verifier::verify(const number_t& message, const number_t& r, const number_t& s) const
    {
      if (r <= 0 || s <= 0 || r >= m_modulus || s >= m_modulus - 1) {
        return false;
      }
      number_t g_h = m_generator.pow_mod(message, m_modulus);
      number_t g_a_r = m_gen_power.pow_mod(r, m_modulus);
      number_t r_s = r.pow_mod(s, m_modulus);
      return g_h == (g_a_r * r_s).mod(m_modulus);
    }

    bool Verifier::verify(const string& message) const
    {
      number_size_t length = message.length();

      // If message is too short for a signature, reject immediately.
      if (length < m_signature_length) {
        return false;
      }

      // Read numbers
      string hash = m_hasher.hash(message.substr(0, length - m_signature_length));
      number_t hash_number = m_converter.binread(hash);
      number_t r = m_converter.binread(message.substr(length - m_signature_length, m_r_length));
      number_t s = m_converter.binread(message.substr(length - m_s_length, m_s_length));

      // Verify
      return verify(hash_number, r, s);
    }

    std::string& Verifier::remove_signature(std::string& message) const
    {
      number_size_t sig_len = signature_length();
      number_size_t length = message.length();
      PREC(SignatureLength, length >= sig_len);
      message.erase(length - sig_len, sig_len);
      return message;
    }

  } // namespace Elgamal

} // namespace Crypto
