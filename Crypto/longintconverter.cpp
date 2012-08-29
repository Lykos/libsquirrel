#include "Crypto/longintconverter.h"
#include "Crypto/preconditionviolation.h"

namespace Crypto {

  using namespace DataStructures;

  LongIntConverter::number_size_t LongIntConverter::fitting_length(const LongInt& number)
  {
    return number.byte_size() - 1;
  }

  LongIntConverter::number_size_t LongIntConverter::required_length(const LongInt& number)
  {
    return number.byte_size();
  }
  
  LongInt LongIntConverter::read_number(const u_int8_t* text, number_size_t length) const
  {
    return LongInt(text, length);
  }

  void LongIntConverter::write_number(const LongInt& number, u_int8_t* text, number_size_t length) const throw(PreconditionViolation)
  {
    number_size_t len = required_length(number);
    PREC(NumberFits, len <= length);
    number.write(text);
    for (number_size_t i = len; i < length; ++i) {
      text[i] = 0;
    }
  }
  
} // namespace Crypto
