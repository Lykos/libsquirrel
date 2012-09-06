#include "types.h"
#include "dh_converter.h"
#include "preconditionviolation.h"
#include "readnumber_macro.h"
#include <climits>

namespace Crypto {

  namespace DH {

    using namespace std;

    const uint_fast16_t Converter::length_length = 4; // Not sizeof(number_size_t) since that type might be longer

    group_t Converter::read_group(const string& raw_group) const
    {
      INIT_READ(raw_group);
      READ_NUMBER(GroupModulusLengthLength, GroupModulusLength, modulus, raw_group);
      READ_NUMBER(GroupGeneratorLengthLength, GroupGeneratorLength, generator, raw_group);
      return {modulus, generator};
    }

    string Converter::write_group(const group_t& group) const
    {
      return write_number(group.modulus) + write_number(group.generator);
    }

    number_t Converter::read_number(const string& raw_number) const
    {
      INIT_READ(raw_number);
      READ_NUMBER(NumberLengthLength, NumberLength, number, raw_number);
      return number;
    }

    string Converter::write_number(const number_t& number) const
    {
      number_size_t number_length = m_converter.byte_size(number);
      return write_length(number_length) + m_converter.binwrite(number, number_length);
    }

    // We use big endian format
    number_size_t Converter::read_length(const string& raw_length) const
    {
      PREC(NumberLengthLength, raw_length.length() >= length_length);
      number_size_t length = 0;
      for (uint_fast16_t i = 0; i < length_length; ++i) {
        length |= raw_length[i] << (length_length - 1 - i) * CHAR_BIT;
      }
      return length;
    }

    string Converter::write_length(number_size_t length) const
    {
      PREC(NumberLengthValue, length <= UINT32_MAX);
      string str (length_length, 0);
      for (uint_fast16_t i = 0; i < length_length; ++i) {
        char c = (char)((length >> (length_length - 1 - i) * CHAR_BIT) & 0xFF);
        str[i] = c;
      }
      return str;
    }

  } // namespace Elgamal

} // namespace Crypto
