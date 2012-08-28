#include "elgamal_converter.h"
#include <climits>

namespace Crypto {

  namespace Elgamal {

    // We use big endian format
    Converter::number_size_t Converter::read_length(const elgamal_byte_t* raw_length)
    {
      return (raw_length[0] << 3 * CHAR_BIT) + (raw_length[1] << 2 * CHAR_BIT) + (raw_length[2] << CHAR_BIT) + raw_length[3];
    }

    void Converter::write_length(number_size_t length, elgamal_byte_t* raw_length)
    {
      raw_length[0] = (length >> 3 * CHAR_BIT) & 0xFF;
      raw_length[1] = (length >> 2 * CHAR_BIT) & 0xFF;
      raw_length[2] = (length >> CHAR_BIT) & 0xFF;
      raw_length[3] = length & 0xFF;
    }

    public_key_t Converter::read_public_key(const elgamal_byte_t* raw_key, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t modulus_length = read_length(raw_key);
      number_t modulus = read_number(raw_key, length);
      raw_key += modulus_length;
      length -= modulus_length;
      assert(length >= sizeof(number_size_t));
      number_size_t generator_length = read_length(raw_key);
      number_t generator = read_number(raw_key, length);
      raw_key += generator_length;
      length -= generator_length;
      number_t gen_power = read_number(raw_key, length);
      return {modulus, generator, gen_power};
    }

    Converter::number_size_t Converter::write_public_key(const public_key_t& public_key, elgamal_byte_t* raw_key)
    {
      number_size_t modulus_length = write_number(public_key.modulus, raw_key);
      raw_key += modulus_length;
      number_size_t generator_length = write_number(public_key.generator, raw_key);
      raw_key += generator_length;
      number_size_t gen_power_length = write_number(public_key.gen_power, raw_key);
      return modulus_length + generator_length + gen_power_length;
    }

    Converter::number_size_t Converter::public_key_length(const public_key_t& public_key) const
    {
      return number_length(public_key.modulus) + number_length(public_key.generator) + number_length(public_key.gen_power);
    }

    private_key_t Converter::read_private_key(const elgamal_byte_t* raw_key, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t modulus_length = read_length(raw_key);
      number_t modulus = read_number(raw_key, length);
      raw_key += modulus_length;
      length -= modulus_length;
      assert(length >= sizeof(number_size_t));
      number_size_t generator_length = read_length(raw_key);
      number_t generator = read_number(raw_key, length);
      raw_key += generator_length;
      length -= generator_length;
      exponent_t exponent = read_number(raw_key, length);
      return {modulus, generator, exponent};
    }

    Converter::number_size_t Converter::write_private_key(const private_key_t& private_key, elgamal_byte_t* raw_key)
    {
      number_size_t modulus_length = write_number(private_key.modulus, raw_key);
      raw_key += modulus_length;
      number_size_t generator_length = write_number(private_key.generator, raw_key);
      raw_key += generator_length;
      number_size_t exponent_length = write_number(private_key.exponent, raw_key);
      return modulus_length + generator_length + exponent_length;
    }

    Converter::number_size_t Converter::private_key_length(const private_key_t& private_key) const
    {
      return number_length(private_key.modulus) + number_length(private_key.generator) + number_length(private_key.exponent);
    }

    group_t Converter::read_group(const elgamal_byte_t* raw_group, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t modulus_length = read_length(raw_group);
      number_t modulus = read_number(raw_group, length);
      raw_group += modulus_length;
      length -= modulus_length;
      number_t generator = read_number(raw_group, length);
      return {modulus, generator};
    }

    Converter::number_size_t Converter::write_group(const group_t& group, elgamal_byte_t* raw_group)
    {
      number_size_t modulus_length = write_number(group.modulus, raw_group);
      raw_group += modulus_length;
      number_size_t generator_length = write_number(group.generator, raw_group);
      return modulus_length + generator_length;
    }

    Converter::number_size_t Converter::group_length(const group_t& group) const
    {
      return number_length(group.modulus) + number_length(group.generator);
    }

    number_t Converter::read_number(const elgamal_byte_t* raw_number, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t number_length = read_length(raw_number);
      assert(length >= sizeof(number_size_t) + number_length);
      return m_converter.read_number(raw_number + sizeof(number_size_t), number_length);
    }

    Converter::number_size_t Converter::write_number(const number_t& number, elgamal_byte_t* raw_number)
    {
      number_size_t number_length = m_converter.number_length(number);
      write_length(number_length, raw_number);
      m_converter.write_number(number, raw_number + sizeof(number_size_t), number_length);
      return sizeof(number_size_t) + number_length;
    }

    Converter::number_size_t Converter::number_length(const number_t& number) const
    {
      return sizeof(number_size_t) + m_converter.number_length(number);
    }

  } // namespace Elgamal

} // namespace Crypto
