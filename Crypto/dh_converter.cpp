#include "Crypto/types.h"
#include "Crypto/dh_converter.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/readnumber_macro.h"
#include <climits>

namespace Crypto {

  namespace DH {

    const number_size_t Converter::length_length = sizeof(number_size_t);

    group_t Converter::read_group(const std::string& raw_group) const
    {
      INIT_READ(raw_group);
      READ_NUMBER(GroupModulusLengthLength, GroupModulusLength, modulus, raw_group);
      READ_NUMBER(GroupGeneratorLengthLength, GroupGeneratorLength, generator, raw_group);
      return {modulus, generator};
    }

    std::string Converter::write_group(const group_t& group) const
    {
      return write_number(group.modulus) + write_number(group.generator);
    }

    number_t Converter::read_number(const std::string& raw_number) const
    {
      INIT_READ(raw_number);
      READ_NUMBER(NumberLengthLength, NumberLength, number, raw_number);
      return number;
    }

    std::string Converter::write_number(const number_t& number) const
    {
      number_size_t number_length = m_converter.required_length(number);
      byte_t *raw_number = new byte_t[number_length];
      m_converter.write_number(number, raw_number + length_length, number_length);
      std::string number_string ((const char*)raw_number);
      return write_length(number_length) + number_string;
    }

    // We use big endian format
    number_size_t Converter::read_length(const std::string& raw_length) const
    {
      return (raw_length[0] << 3 * CHAR_BIT) + (raw_length[1] << 2 * CHAR_BIT) + (raw_length[2] << CHAR_BIT) + raw_length[3];
    }

    std::string Converter::write_length(number_size_t length) const
    {
      return std::string({(length >> 3 * CHAR_BIT) & 0xFF,
                         (length >> 2 * CHAR_BIT) & 0xFF,
                         (length >> CHAR_BIT) & 0xFF,
                         length & 0xFF});
    }

  } // namespace Elgamal

} // namespace Crypto
