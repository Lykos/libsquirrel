#include "Crypto/elgamal_encrypter.h"
#include "Crypto/elgamal_converter.h"
#include "Crypto/longintconverter.h"

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
      m_plain_length (LongIntConverter::fitting_length(m_modulus)),
      m_key_part_length (LongIntConverter::required_length(m_modulus)),
      m_cipher_length (m_key_part_length + sizeof(number_t::part_type) + m_plain_length)
    {}

    Encrypter::Encrypter(const elgamal_byte_t* raw_public_key, number_size_t length)
    {
      Converter conv;
      public_key_t public_key = conv.read_public_key(raw_public_key, length);
      m_modulus = public_key.modulus;
      m_generator = public_key.generator;
      m_gen_power = public_key.gen_power;
      m_exponent_distribution = UniformLongIntDistribution(ZERO, (m_modulus >> 1) - TWO);
      m_plain_length = LongIntConverter::fitting_length(m_modulus);
      m_key_part_length = LongIntConverter::required_length(m_modulus);
      m_cipher_length = m_key_part_length + sizeof(number_t::part_type) + m_plain_length;
    }

    Encrypter::Encrypter(const Encrypter& other):
      m_modulus (other.m_modulus),
      m_generator (other.m_generator),
      m_gen_power (other.m_gen_power),
      m_exponent_distribution (other.m_exponent_distribution),
      m_plain_length (other.m_plain_length),
      m_key_part_length (other.m_key_part_length),
      m_cipher_length (other.m_cipher_length)
    {
    }

    Encrypter::Encrypter(Encrypter&& other):
      m_modulus (std::move(other.m_modulus)),
      m_generator (std::move(other.m_generator)),
      m_gen_power (std::move(other.m_gen_power)),
      m_exponent_distribution (std::move(other.m_exponent_distribution)),
      m_plain_length (std::move(other.m_plain_length)),
      m_key_part_length (std::move(other.m_key_part_length)),
      m_cipher_length (std::move(other.m_cipher_length))
    {
    }

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
      return {(plain * key_inv) % m_modulus, own_gen_power};
    }

    void Encrypter::encrypt(const elgamal_byte_t* plain, elgamal_byte_t* cipher)
    {
      // Convert to numbers
      number_t plain_number = m_converter.read_number(plain, m_plain_length);

      // Encrypt and generate additional key part
      cipher_t cipher_pair = encrypt(plain_number);

      // Convert back back
      m_converter.write_number(cipher_pair.cipher, cipher, m_plain_length + sizeof(number_t::part_type));
      m_converter.write_number(cipher_pair.gen_power, cipher + m_plain_length + sizeof(number_t::part_type), m_key_part_length);
    }
    
  } // namespace Elgamal

} // namespace Crypto
