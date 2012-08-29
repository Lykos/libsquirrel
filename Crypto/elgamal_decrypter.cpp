#include "Crypto/elgamal_decrypter.h"
#include "DataStructures/arithmetichelper.h"
#include "Crypto/elgamal_converter.h"
#include "Crypto/longintconverter.h"

namespace Crypto {

  namespace Elgamal {

    static const number_t ONE = 1;

    Decrypter::Decrypter(const private_key_t &private_key):
      m_modulus (private_key.modulus),
      m_exponent (private_key.exponent),
      // Note that valid texts fit into fitting_length(m_modulus), but at this point, we also
      // have to consider invalid ones.
      m_plain_length (LongIntConverter::required_length(m_modulus)),
      m_key_part_length (LongIntConverter::required_length(m_modulus)),
      m_cipher_part_length (LongIntConverter::required_length(m_modulus)),
      m_cipher_length (m_key_part_length + m_cipher_part_length)
    {}

    Decrypter::Decrypter(const elgamal_byte_t* raw_private_key, number_size_t length)
    {
      Converter conv;
      private_key_t private_key = conv.read_private_key(raw_private_key, length);
      m_modulus = private_key.modulus;
      m_exponent = private_key.exponent;
      m_plain_length = LongIntConverter::required_length(m_modulus);
      m_key_part_length = LongIntConverter::required_length(m_modulus);
      m_cipher_part_length = LongIntConverter::required_length(m_modulus);
      m_cipher_length = m_key_part_length + m_cipher_part_length;
    }

    number_t Decrypter::decrypt(const number_t& cipher, const number_t& other_gen_power) const
    {
      number_t key = other_gen_power.pow_mod(m_exponent, m_modulus);
      return (key * cipher) % m_modulus;
    }

    void Decrypter::decrypt(const elgamal_byte_t* cipher, elgamal_byte_t* plain) const
    {
      // Convert to numbers
      number_t cipher_number = m_converter.read_number(cipher, m_cipher_part_length);
      number_t cipher_power = m_converter.read_number(cipher + m_cipher_part_length, m_key_part_length);

      // Decrypt
      number_t plain_number = decrypt(cipher_number, cipher_power);

      // Convert back
      m_converter.write_number(plain_number, plain, m_plain_length);
    }
    
  } // namespace Elgamal

} // namespace Crypto
