#include "elgamal_decrypter.h"
#include "LongArithmetic/arithmetichelper.h"
#include "elgamal_converter.h"
#include "LongArithmetic/longintconverter.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include <string>

using namespace std;
using namespace LongArithmetic;

namespace Crypto {

  namespace Elgamal {

    static const number_t ONE = 1;

    Decrypter::Decrypter(const private_key_t &private_key):
      m_modulus (private_key.modulus),
      m_exponent (private_key.exponent),
      m_plain_length (LongIntConverter::byte_size(m_modulus) - 1),
      m_key_part_length (LongIntConverter::byte_size(m_modulus)),
      m_cipher_part_length (LongIntConverter::byte_size(m_modulus)),
      m_cipher_length (m_key_part_length + m_cipher_part_length)
    {}

    Decrypter::Decrypter(const std::string& raw_private_key)
    {
      Converter conv;
      private_key_t private_key = conv.read_private_key(raw_private_key);
      m_modulus = private_key.modulus;
      m_exponent = private_key.exponent;
      m_plain_length = LongIntConverter::byte_size(m_modulus) - 1;
      m_key_part_length = LongIntConverter::byte_size(m_modulus);
      m_cipher_part_length = LongIntConverter::byte_size(m_modulus);
      m_cipher_length = m_key_part_length + m_cipher_part_length;
    }

    number_t Decrypter::decrypt(const number_t& cipher, const number_t& other_gen_power) const
    {
      number_t key = other_gen_power.pow_mod(m_exponent, m_modulus);
      return (key * cipher) % m_modulus;
    }

    string Decrypter::decrypt(const string& cipher) const
    {
      PREC(CipherBlockLength, cipher.length() == m_cipher_length);

      // Convert to numbers
      number_t cipher_number = m_converter.binread(cipher.substr(0, m_cipher_part_length));
      number_t cipher_power = m_converter.binread(cipher.substr(m_cipher_part_length, m_key_part_length));

      // Decrypt
      number_t plain_number = decrypt(cipher_number, cipher_power);

      // Convert back
      PREC(DecryptedPlainBlockLength, m_converter.byte_size(plain_number) <= m_plain_length);
      string plain = m_converter.binwrite(plain_number, m_plain_length);
      assert(plain.length() == m_plain_length);
      return plain;
    }
    
  } // namespace Elgamal

} // namespace Crypto
