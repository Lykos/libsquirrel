#include "types.h"
#include "dh_converter.h"
#include "preconditionviolation.h"
#include "readnumber_macro.h"
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
      number_size_t number_length = m_converter.byte_size(number);
      return write_length(number_length) + m_converter.binwrite(number, number_length);
    }

    // We use big endian format
    number_size_t Converter::read_length(const std::string& raw_length) const
    {
      return (raw_length[0] << 3 * CHAR_BIT) + (raw_length[1] << 2 * CHAR_BIT) + (raw_length[2] << CHAR_BIT) + raw_length[3];
    }

    std::string Converter::write_length(number_size_t length) const
    {
      return std::string({(char)((length >> 3 * CHAR_BIT) & 0xFF),
                         (char)((length >> 2 * CHAR_BIT) & 0xFF),
                         (char)((length >> CHAR_BIT) & 0xFF),
                         (char)(length & 0xFF)});
    }

  } // namespace Elgamal

} // namespace Crypto
