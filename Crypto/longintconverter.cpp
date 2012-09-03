#include "Crypto/longintconverter.h"
#include "Crypto/preconditionviolation.h"
#include <cstring>

using namespace std;

namespace Crypto {

  using namespace DataStructures;

  number_size_t LongIntConverter::fitting_length(const LongInt& number)
  {
    return number.byte_size() - 1;
  }

  number_size_t LongIntConverter::required_length(const LongInt& number)
  {
    return number.byte_size();
  }

  LongInt LongIntConverter::read_number(const string& text) const
  {
    return LongInt((const byte_t*)text.data(), text.length());
  }

  string LongIntConverter::write_number(const LongInt& number, number_size_t length) const throw(PreconditionViolation)
  {
    number_size_t len = required_length(number);
    PREC(NumberFits, len <= length);
    byte_t *text = new byte_t[length];
    number_size_t padding = length - len;
    memset(text, 0, padding * sizeof(byte_t));
    number.write(text + padding);
    string bla ((const char*)text, length);
    delete[] text;
    return bla;
  }
  
} // namespace Crypto
