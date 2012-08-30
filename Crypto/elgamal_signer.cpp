#include "elgamal_signer.h"
#include "elgamal_types.h"
#include "elgamal_converter.h"
#include "DataStructures/arithmetichelper.h"
#include "DataStructures/longint.h"
#include "sha2hasher.h"

namespace Crypto {

  namespace Elgamal {

    using namespace DataStructures;

    using namespace ArithmeticHelper;

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

    Signer::Signer(const elgamal_byte_t* raw_private_key, number_size_t length)
    {
      Converter conv;
      private_key_t private_key = conv.read_private_key(raw_private_key, length);
      m_modulus = private_key.modulus;
      m_generator = private_key.generator;
      m_phi_modulus = m_modulus - ONE;
      m_exponent = private_key.exponent;
      m_k_distribution = UniformLongIntDistribution(ONE, m_phi_modulus - ONE);
      m_r_length = m_modulus.size() * sizeof(number_t::part_type);
      m_s_length = m_modulus.size() * sizeof(number_t::part_type);
      m_signature_length = m_r_length + m_s_length;
    }

    Signer::Signer(const Signer& other):
      m_modulus (other.m_modulus),
      m_generator (other.m_generator),
      m_phi_modulus (other.m_phi_modulus),
      m_exponent (other.m_exponent),
      m_k_distribution (other.m_k_distribution),
      m_r_length (other.m_r_length),
      m_s_length (other.m_s_length),
      m_signature_length (other.m_signature_length)
    {
    }

    Signer::Signer(Signer&& other):
      m_modulus (std::move(other.m_modulus)),
      m_generator (std::move(other.m_generator)),
      m_phi_modulus (std::move(other.m_phi_modulus)),
      m_exponent (std::move(other.m_exponent)),
      m_k_distribution (std::move(other.m_k_distribution)),
      m_r_length (std::move(other.m_r_length)),
      m_s_length (std::move(other.m_s_length)),
      m_signature_length (std::move(other.m_signature_length))
    {
    }

    Signer& Signer::operator=(const Signer& other)
    {
      if (this == &other) {
        return *this;
      }
      m_modulus = other.m_modulus;
      m_generator = other.m_generator;
      m_phi_modulus = other.m_phi_modulus;
      m_exponent = other.m_exponent;
      m_k_distribution = other.m_k_distribution;
      m_r_length = other.m_r_length;
      m_s_length = other.m_s_length;
      m_signature_length = other.m_signature_length;
      return *this;
    }

    Signer& Signer::operator=(Signer&& other)
    {
      if (this == &other) {
        return *this;
      }
      m_modulus = std::move(other.m_modulus);
      m_generator = std::move(other.m_generator);
      m_phi_modulus = std::move(other.m_phi_modulus);
      m_exponent = std::move(other.m_exponent);
      m_k_distribution = std::move(other.m_k_distribution);
      m_r_length = other.m_r_length;
      m_s_length = other.m_s_length;
      m_signature_length = other.m_signature_length;
      return *this;
    }

    Signer::~Signer() {}

    Signer::signature_t Signer::sign(const number_t& message)
    {
      number_t r, s;
      do {
        number_t k;
        do {
          k = m_k_distribution(m_random_generator);
        } while (gcd(k, m_phi_modulus) != ONE);
        r = m_generator.pow_mod(k, m_modulus);
        number_t k_inv = k.mult_inv_mod(m_modulus - 1);
        s = ((message - m_exponent * r) * k_inv).mod(m_modulus - 1);
      } while (s == ZERO);
      return {r, s};
    }

    ulong Signer::sign(elgamal_byte_t* message, ulong length)
    {
      // Generate hash of message
      elgamal_byte_t hash[32];
      hasher.hash(message, length, hash + 0);
      number_t hash_number = m_converter.read_number(hash, 32);

      // Sign hash
      signature_t sig = sign(hash_number);

      // Append signature
      m_converter.write_number(sig.r, message + length, m_r_length);
      m_converter.write_number(sig.s, message + length + m_r_length, m_s_length);
      return length + m_signature_length;
    }
    
  } // namespace Elgamal

} // namespace Crypto