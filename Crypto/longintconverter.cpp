#include "Crypto/longintconverter.h"
#include "Crypto/preconditionviolation.h"

namespace Crypto {

  using namespace DataStructures;
  
  LongInt LongIntConverter::read_number(const u_int8_t* text, number_size_t length) const
  {
    LongInt::packed_longint_t packed;
    packed.sign = true;
    assert(length % sizeof(unsigned int) == 0);
    packed.num_parts = length / sizeof(unsigned int);
    // If it is converted back using this class, it is no problem if the machine is actually big endian.
    packed.parts = (unsigned int*) text;
    return LongInt(packed);
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
