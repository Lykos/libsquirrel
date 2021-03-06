#include "elgamal_encrypter.h"
#include "elgamal_converter.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include "LongArithmetic/longintconverter.h"
#include <string>

using namespace std;

namespace Crypto {

  namespace Elgamal {
    
    using namespace LongArithmetic;

    static const number_t ZERO = 0;

    static const number_t ONE = 1;

    static const number_t TWO = 2;

    Encrypter::Encrypter(const public_key_t &public_key):
      m_modulus (public_key.modulus),
      m_generator (public_key.generator),
      m_gen_power (public_key.gen_power),
      m_exponent_distribution (ZERO, (m_modulus >> 1) - TWO),
      m_plain_length (LongIntConverter::byte_size(m_modulus) - 1),
      m_key_part_length (LongIntConverter::byte_size(m_modulus)),
      m_cipher_part_length (LongIntConverter::byte_size(m_modulus)),
      m_cipher_length (m_key_part_length + m_cipher_part_length)
    {}

    Encrypter::Encrypter(const std::string& raw_public_key)
    {
      Converter conv;
      public_key_t public_key = conv.read_public_key(raw_public_key);
      m_modulus = public_key.modulus;
      m_generator = public_key.generator;
      m_gen_power = public_key.gen_power;
      m_exponent_distribution = UniformLongIntDistribution(ZERO, (m_modulus >> 1) - TWO);
      m_plain_length = LongIntConverter::byte_size(m_modulus) - 1;
      m_key_part_length = LongIntConverter::byte_size(m_modulus);
      m_cipher_part_length = LongIntConverter::byte_size(m_modulus);
      m_cipher_length = m_key_part_length + m_cipher_part_length;
    }

    Encrypter::Encrypter(const Encrypter& other):
      m_modulus (other.m_modulus),
      m_generator (other.m_generator),
      m_gen_power (other.m_gen_power),
      m_exponent_distribution (other.m_exponent_distribution),
      m_plain_length (other.m_plain_length),
      m_key_part_length (other.m_key_part_length),
      m_cipher_part_length (other.m_cipher_part_length),
      m_cipher_length (other.m_cipher_length)
    {}

    Encrypter::Encrypter(Encrypter&& other):
      m_modulus (std::move(other.m_modulus)),
      m_generator (std::move(other.m_generator)),
      m_gen_power (std::move(other.m_gen_power)),
      m_exponent_distribution (std::move(other.m_exponent_distribution)),
      m_plain_length (other.m_plain_length),
      m_key_part_length (other.m_key_part_length),
      m_cipher_part_length (other.m_cipher_part_length),
      m_cipher_length (other.m_cipher_length)
    {}

    Encrypter& Encrypter::operator=(const Encrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      m_modulus = other.m_modulus;
      m_generator = other.m_generator;
      m_gen_power = other.m_gen_power;
      m_exponent_distribution = other.m_exponent_distribution;
      m_plain_length = other.m_plain_length;
      m_key_part_length = other.m_key_part_length;
      m_cipher_part_length = other.m_cipher_part_length;
      m_cipher_length = other.m_cipher_length;
      return *this;
    }

    Encrypter& Encrypter::operator=(Encrypter&& other)
    {
      if (this == &other) {
        return *this;
      }
      m_modulus = std::move(other.m_modulus);
      m_generator = std::move(other.m_generator);
      m_gen_power = std::move(other.m_gen_power);
      m_exponent_distribution = std::move(other.m_exponent_distribution);
      m_plain_length = other.m_plain_length;
      m_key_part_length = other.m_key_part_length;
      m_cipher_part_length = other.m_cipher_part_length;
      m_cipher_length = other.m_cipher_length;
      return *this;
    }

    Encrypter::~Encrypter() {}

    Encrypter::cipher_t Encrypter::encrypt(const number_t& plain)
    {
      // Generate additional key part
      exponent_t exponent = m_exponent_distribution(m_random_generator);
      number_t own_gen_power = m_generator.pow_mod(exponent, m_modulus);

      // Calculate encryption key
      number_t key = m_gen_power.pow_mod(exponent, m_modulus);
      number_t key_inv = key.mult_inv_mod(m_modulus);

      // encrypt
      number_t cipher = (plain * key_inv) % m_modulus;
      return {cipher, own_gen_power};
    }

    string Encrypter::encrypt(const string& plain)
    {
      PREC(PlainBlockLength, plain.length() == m_plain_length);

      // Convert to numbers
      number_t plain_number = m_converter.binread(plain);

      // Encrypt and generate additional key part
      cipher_t cipher_pair = encrypt(plain_number);

      // Convert back back
      string cipher = m_converter.binwrite(cipher_pair.cipher, m_cipher_part_length)
          + m_converter.binwrite(cipher_pair.gen_power, m_key_part_length);
      assert(cipher.length() == m_cipher_length);
      return cipher;
    }
    
  } // namespace Elgamal

} // namespace Crypto
