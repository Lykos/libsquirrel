#include "Crypto/longintconverter.h"
#include "Crypto/preconditionviolation.h"

namespace Crypto {

  using namespace DataStructures;

  LongIntConverter::number_size_t LongIntConverter::fitting_length(const LongInt& number)
  {
    return (number.size() - 1) * sizeof(LongInt::part_type) + log2(number.part_at(number.size() - 1)) / CHAR_BIT;
  }

  LongIntConverter::number_size_t LongIntConverter::required_length(const LongInt& number)
  {
    return fitting_length(number) + 1;
  }
  
  LongInt LongIntConverter::read_number(const u_int8_t* text, number_size_t length) const
  {
    return LongInt(text, length);
  }

  LongIntConverter::number_size_t LongIntConverter::number_length(const LongInt& number) const
  {
    return sizeof(LongInt::part_type) * number.size();
  }

  void LongIntConverter::write_number(const LongInt& number, u_int8_t* text, number_size_t length) const
  {
    number_size_t len = number_length(number);
    PREC(NumberFits, len <= length);
    LongInt::packed_longint_t packed = number.pack();
    for (number_size_t i = 0; i < packed.num_parts; ++i) {
      for (number_size_t j = 0; j < sizeof(unsigned int); ++j) {
        text[i * sizeof(unsigned int) + j] = (packed.parts[i] >> j * 8) & 0xFF;
      }
    }
    assert(packed.num_parts * sizeof(unsigned int) == len);
    for (number_size_t i = len; i < length; ++i) {
      text[i] = 0;
    }
  }
  
} // namespace Crypto
