#include "elgamal_converter.h"

namespace Crypto {

  namespace Elgamal {

    public_key_t Converter::read_public_key(const elgamal_byte_t* raw_key, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t modulus_length = DH::Converter::read_length(raw_key);
      number_t modulus = DH::Converter::read_number(raw_key, length);
      raw_key += modulus_length;
      length -= modulus_length;
      assert(length >= sizeof(number_size_t));
      number_size_t generator_length = DH::Converter::read_length(raw_key);
      number_t generator = DH::Converter::read_number(raw_key, length);
      raw_key += generator_length;
      length -= generator_length;
      number_t gen_power = DH::Converter::read_number(raw_key, length);
      return {modulus, generator, gen_power};
    }

    Converter::number_size_t Converter::write_public_key(const public_key_t& public_key, elgamal_byte_t* raw_key)
    {
      number_size_t modulus_length = DH::Converter::write_number(public_key.modulus, raw_key);
      raw_key += modulus_length;
      number_size_t generator_length = DH::Converter::write_number(public_key.generator, raw_key);
      raw_key += generator_length;
      number_size_t gen_power_length = DH::Converter::write_number(public_key.gen_power, raw_key);
      return modulus_length + generator_length + gen_power_length;
    }

    Converter::number_size_t Converter::public_key_length(const public_key_t& public_key) const
    {
      return number_length(public_key.modulus) + number_length(public_key.generator) + number_length(public_key.gen_power);
    }

    private_key_t Converter::read_private_key(const elgamal_byte_t* raw_key, number_size_t length)
    {
      assert(length >= sizeof(number_size_t));
      number_size_t modulus_length = DH::Converter::read_length(raw_key);
      number_t modulus = DH::Converter::read_number(raw_key, length);
      raw_key += modulus_length;
      length -= modulus_length;
      assert(length >= sizeof(number_size_t));
      number_size_t generator_length = DH::Converter::read_length(raw_key);
      number_t generator = DH::Converter::read_number(raw_key, length);
      raw_key += generator_length;
      length -= generator_length;
      exponent_t exponent = DH::Converter::read_number(raw_key, length);
      return {modulus, generator, exponent};
    }

    Converter::number_size_t Converter::write_private_key(const private_key_t& private_key, elgamal_byte_t* raw_key)
    {
      number_size_t modulus_length = DH::Converter::write_number(private_key.modulus, raw_key);
      raw_key += modulus_length;
      number_size_t generator_length = DH::Converter::write_number(private_key.generator, raw_key);
      raw_key += generator_length;
      number_size_t exponent_length = DH::Converter::write_number(private_key.exponent, raw_key);
      return modulus_length + generator_length + exponent_length;
    }

    Converter::number_size_t Converter::private_key_length(const private_key_t& private_key) const
    {
      return number_length(private_key.modulus) + number_length(private_key.generator) + number_length(private_key.exponent);
    }
    
  } // namespace Elgamal
} // namespace Crypto
