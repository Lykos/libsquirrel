#include "longintconverter.h"
#include "longint.h"
#include "arithmetichelper.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include "debug.h"
#include <climits>
#include <string>

namespace LongArithmetic {

  using namespace std;
  using namespace ArithmeticHelper;

  LongIntConverter::size_type LongIntConverter::byte_size(const LongInt& number)
  {
    arithmetic_assert(number.size() > 0);
    size_type last_index = number.size() - 1;
    return last_index * sizeof(part_type) + log2(number.m_content[last_index]) / CHAR_BIT + 1;
  }

  LongIntConverter::size_type LongIntConverter::part_size(size_type bytes)
  {
    return (bytes - 1) / sizeof(part_type) + 1;
  }

  LongInt LongIntConverter::binread(const string& text) const
  {
    size_type bytes = text.length();
    LongInt number;
    number.pad_zeros(part_size(bytes));
    for (size_type i = 0; i < bytes; ++i) {
      part_type byte = (unsigned char)(text[bytes - 1 - i]);
      number.m_content[i / sizeof(part_type)] |= byte << (i % sizeof(part_type)) * CHAR_BIT;
    }
    number.remove_zeros();
    return number;
  }

  string LongIntConverter::binwrite(const LongInt &number) const
  {
    return binwrite(number, byte_size(number));
  }

  string LongIntConverter::binwrite(const LongInt& number, size_type length) const
  {
    size_type bytes = byte_size(number);
    PREC(NumberLength, length >= bytes);
    size_type start = length - bytes;
    size_type size = number.size();
    part_type first_digit = number.m_content[size - 1];
    size_type first_length = log2(first_digit) / CHAR_BIT + 1;
    assert(first_length + sizeof(part_type) * (size - 1) == bytes);
    string str (length, 0);
    for (uint_fast16_t i = 0; i < first_length; ++i) {
      str[start + i] = (first_digit >> (first_length - i - 1) * CHAR_BIT) & 0xFF;
    }
    for (size_type i = 0; i < size - 1; ++i) {
      for (uint_fast16_t j = 0; j < sizeof(part_type); ++j) {
        char byte = (number.m_content[size - i - 2] >> (sizeof(part_type) - j - 1) * CHAR_BIT) & 0xFF;
        str[start + first_length + sizeof(part_type) * i + j] = byte;
      }
    }
    return str;
  }

  template <typename T>
  LongInt LongIntConverter::unpack(const packed_longint<T>& packed) const
  {
    size_type bytes = (packed.size - 1) * sizeof(T) + log2(packed.parts[packed.size - 1]) / CHAR_BIT + 1;
    LongInt number;
    number.m_positive = packed.positive;
    number.pad_zeros(part_size(bytes));
    for (size_type i = 0; i < bytes; ++i) {
      part_type byte = (packed[i / sizeof(T)] >> (i % sizeof(T)) * CHAR_BIT) & 0xFF;
      number.m_content[i / sizeof(part_type)] |= byte << (i % sizeof(part_type)) * CHAR_BIT;
    }
    number.remove_zeros();
    return number;
  }

  template <typename T>
  LongIntConverter::packed_longint<T> LongIntConverter::pack(const LongInt& number) const
  {
    size_type bytes = byte_size(number);
    size_type size = (bytes - 1) / sizeof(T) + 1;
    T* parts = new T[size];
    for (size_type i = 0; i < bytes; ++i) {
      T byte = (number.m_content[i / sizeof(part_type)] >> (i % sizeof(part_type)) * CHAR_BIT) & 0xFF;
      parts[i / sizeof(T)] |= byte << (i % sizeof(T)) * CHAR_BIT;
    }
    return {number.m_positive, size, parts};
  }

  LongInt LongIntConverter::from_mpz(const mpz_class& mpz) const
  {
    // TODO Work in progress
    LongInt number;
    number.m_content = LongInt::part_list (mpz.get_mpz_t()->_mp_size * sizeof(mp_limb_t) / sizeof(part_type));
    mpz_export(&number.m_content[0], nullptr, -1, sizeof(part_type), 0, 0, mpz.get_mpz_t());
    return number;
  }

  mpz_class LongIntConverter::to_mpz(const LongInt& number) const
  {
    // TODO Work in progress
    mpz_t c;
    mpz_import(c, number.size(), -1, sizeof(part_type), 0, 0, &number.m_content[0]);
    return mpz_class(c);
  }

} // namespace LongArithmetic
