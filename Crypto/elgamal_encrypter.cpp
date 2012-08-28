#include "elgamal_encrypter.h"
#include "longintconverter.h"

namespace Crypto {

  namespace Elgamal {
    
    using namespace DataStructures;

    static const number_t ZERO = 0;

    static const number_t ONE = 1;

    static const number_t TWO = 2;

    Encrypter::Encrypter(const public_key_t &public_key):
      m_modulus (public_key.modulus),
      m_generator (public_key.generator),
      m_gen_power (public_key.gen_power),
      m_exponent_distribution (ZERO, (m_modulus >> 1) - TWO),
      m_plain_length ((m_modulus.size() - 1) * sizeof(number_t::part_type)),
      m_exponent_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_cipher_length (m_exponent_length + sizeof(number_t::part_type) + m_plain_length)
    {
    }

    void Encrypter::encrypt(const elgamal_byte_t* plain, elgamal_byte_t* cipher)
    {
      // Convert to numbers
      number_t plain_number = m_converter.read_number(plain, m_plain_length);

      // Encrypt and generate additional key part
      exponent_t exponent = m_exponent_distribution(m_random_generator);
      number_t own_gen_power = m_generator.pow_mod(exponent, m_modulus);
      number_t key = m_gen_power.pow_mod(exponent, m_modulus);
      number_t key_inv = key.mult_inv_mod(m_modulus);
      number_t cipher_number = (plain_number * key_inv) % m_modulus;

      // Convert back back
      m_converter.write_number(cipher_number, cipher, m_plain_length + sizeof(number_t::part_type));
      m_converter.write_number(own_gen_power, cipher + m_plain_length + sizeof(number_t::part_type), m_exponent_length);
    }
    
  } // namespace Elgamal

} // namespace Crypto
