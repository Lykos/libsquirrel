#include "Crypto/dh_converter.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/readnumber_macro.h"
#include <climits>

namespace Crypto {

  namespace DH {

    const Converter::number_size_t Converter::length_length = sizeof(Converter::number_size_t);

    group_t Converter::read_group(const dh_byte_t* raw_group, number_size_t length) const
    {
      READ_NUMBER(GroupModulusLengthLength, GroupModulusLength, modulus, raw_group);
      READ_NUMBER(GroupGeneratorLengthLength, GroupGeneratorLength, generator, raw_group);
      return {modulus, generator};
    }

    Converter::number_size_t Converter::write_group(const group_t& group, dh_byte_t* raw_group) const
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

    number_t Converter::read_number(const dh_byte_t* raw_number, number_size_t length) const
    {
      READ_NUMBER(NumberLengthLength, NumberLength, number, raw_number);
      return number;
    }

    Converter::number_size_t Converter::write_number(const number_t& number, dh_byte_t* raw_number) const
    {
      number_size_t number_length = m_converter.required_length(number);
      write_length(number_length, raw_number);
      m_converter.write_number(number, raw_number + length_length, number_length);
      return length_length + number_length;
    }

    Converter::number_size_t Converter::number_length(const number_t& number) const
    {
      return length_length + m_converter.required_length(number);
    }


    // We use big endian format
    Converter::number_size_t Converter::read_length(const dh_byte_t* raw_length) const
    {
      return (raw_length[0] << 3 * CHAR_BIT) + (raw_length[1] << 2 * CHAR_BIT) + (raw_length[2] << CHAR_BIT) + raw_length[3];
    }

    void Converter::write_length(number_size_t length, dh_byte_t* raw_length) const
    {
      raw_length[0] = (length >> 3 * CHAR_BIT) & 0xFF;
      raw_length[1] = (length >> 2 * CHAR_BIT) & 0xFF;
      raw_length[2] = (length >> CHAR_BIT) & 0xFF;
      raw_length[3] = length & 0xFF;
    }

  } // namespace Elgamal

} // namespace Crypto
