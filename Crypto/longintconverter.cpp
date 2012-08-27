#include "longintconverter.h"

namespace Crypto {

  using namespace DataStructures;
  
  LongInt LongIntConverter::convert(const u_int8_t* text, uint length)
  {
    LongInt::packed_longint_t packed;
    packed.sign = true;
    packed.num_parts = length / sizeof(unsigned int);
    // If it is converted back using this class, it is no problem if the machine is actually big endian.
    packed.parts = (unsigned int*) text;
    return LongInt(packed);
  }

  void LongIntConverter::convert(const LongInt& number, u_int8_t* text, uint length)
  {
    LongInt::packed_longint_t packed = number.pack();
    assert(length >= sizeof(unsigned int) * packed.num_parts);
    for (uint i = 0; i < packed.num_parts; ++i) {
      for (uint j = 0; j < sizeof(unsigned int); ++j) {
        text[i * sizeof(unsigned int) + j] = (packed.parts[i] >> j * 8) & 0xFF;
      }
    }
    for (uint i = packed.num_parts * sizeof(unsigned int); i < length; ++i) {
      text[i] = 0;
    }
  }
  
} // namespace Crypto
