#include "elgamal_decrypter.h"
#include "arithmetichelper.h"

namespace Crypto {

  namespace Elgamal {

    using namespace DataStructures::ArithmeticHelper;

    static const number_t ONE = 1;

    Decrypter::Decrypter(const private_key_t &private_key):
      m_modulus (private_key.modulus),
      m_exponent (private_key.exponent),
      m_plain_length ((m_modulus.size() - 1) * sizeof(number_t::part_type)),
      m_exponent_length (m_modulus.size() * sizeof(number_t::part_type)),
      m_cipher_length (m_exponent_length + sizeof(number_t::part_type) + m_plain_length)
    {
    }

    void Decrypter::decrypt(const elgamal_byte_t* cipher, elgamal_byte_t* plain)
    {
      // Convert to numbers
      number_t cipher_number = m_converter.read_number(cipher, m_plain_length + sizeof(number_t::part_type));
      number_t cipher_power = m_converter.read_number(cipher + m_plain_length + sizeof(number_t::part_type), m_exponent_length);

      // Decrypt
      number_t key = cipher_power.pow_mod(m_exponent, m_modulus);
      number_t result = (cipher_number * key) % m_modulus;

      // Convert back
      m_converter.write_number(result, plain, m_plain_length);
    }
    
  } // namespace Elgamal

} // namespace Crypto
