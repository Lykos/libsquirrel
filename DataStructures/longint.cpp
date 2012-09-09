#include "longint.h"
#include "algebrahelper.h"
#include "multiply.h"
#include "divide.h"
#include "add.h"
#include "subtract.h"
#include "assembly.h"
#include "ring.h"
#include <cmath>
#include <sstream>
#include <cstdio>
#include <string>
#include <climits>

namespace DataStructures {

  using namespace ArithmeticHelper;
  using namespace LongArithmetic;
  using namespace std;

  static const unsigned int DECIMAL_BUFFER_SIZE = (LongInt::PART_SIZE * 1233) >> 12; // Calculates log_10(2^PART_SIZE)
  static const unsigned int HEXADECIMAL_BUFFER_SIZE = (LongInt::PART_SIZE / 4); // Calculates log_16(2^PART_SIZE)
  static const unsigned int OCTAL_BUFFER_SIZE = (LongInt::PART_SIZE / 3); // Calculates log_8(2^PART_SIZE)

  static const string HEXADECIMAL_BASE = "0x";
  static const string OCTAL_BASE = "0";

  static const LongInt TEN (10);
  static const LongInt ZERO (0);
  static const LongInt ONE (1);
  static const LongInt TWO (2);
  static const LongInt MINUS_ONE (-1);

  static const Ring<LongInt> RING(ZERO, ONE);

  static const LongInt TEN_BUFFER_FACTOR (TEN.pow(DECIMAL_BUFFER_SIZE));

  static const uint_fast8_t base (10);

  const LongInt& LongInt::zero()
  {
    return ZERO;
  }

  const LongInt& LongInt::one()
  {
    return ONE;
  }

  const Ring<LongInt>& LongInt::ring()
  {
    return RING;
  }

  ostream& operator<<(ostream& out, const LongInt& longInt)
  {
    ios_base::fmtflags ff = out.flags();
    if (!longInt.m_positive) {
      out << "-";
    } else if (ff & ios_base::showpos) {
      out << "+";
    }
    if (longInt.size() == 1) {
      out << longInt.m_content[0];
    } else if (ff & ios_base::hex) {
      if (ff & ios_base::showbase) {
        out << HEXADECIMAL_BASE;
      }
      longInt.write_hexadecimal(out);
    } else if (ff & ios_base::oct) {
      if (ff & ios_base::showbase) {
        out << OCTAL_BASE;
      }
      longInt.write_octal(out);
    } else {
      longInt.write_decimal(out);
    }
    return out;
  }

  istream& operator>>(istream& in, LongInt& longInt)
  {
    ios_base::fmtflags ff = in.flags();
    string s;
    in >> s;
    LongInt::size_type length = s.length();
    LongInt::size_type start_index = longInt.read_sign(s);
    arithmetic_assert(start_index <= length);
    PREC(NoDigits, start_index < length);
    if (ff & ios_base::hex) {
      longInt.read_hexadecimal(s, start_index);
    } else if (ff & ios_base::oct) {
      longInt.read_octal(s, start_index);
    } else {
      longInt.read_decimal(s, start_index);
    }
    return in;
  }

  LongInt::LongInt():
    m_positive (true)
  {
    m_content.push_back(0);
  }

  LongInt::LongInt(long long int initial):
    m_positive (initial >= 0)
  {
    m_content.push_back(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned long long int initial):
    m_positive (true)
  {
    m_content.push_back(initial);
  }

  LongInt::LongInt(long int initial):
    m_positive (initial >= 0)
  {
    m_content.push_back(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned long int initial):
    m_positive (true)
  {
    m_content.push_back(initial);
  }

  LongInt::LongInt(int initial):
    m_positive (initial >= 0)
  {
    m_content.push_back(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned int initial):
    m_positive (true)
  {
    m_content.push_back(initial);
  }

  template <typename FLOAT_TYPE, typename INT_TYPE, int MANTISSA, int EXPONENT, int BIAS>
  inline void LongInt::convert_from(FLOAT_TYPE f)
  {
    static_assert(sizeof(INT_TYPE) == sizeof(FLOAT_TYPE), "Incompatible sizes.");
    static_assert(MANTISSA + EXPONENT + 1 == CHAR_BIT * sizeof(FLOAT_TYPE), "Invalid exponent or mantissa size.");
    static_assert(numeric_limits<INT_TYPE>::is_integer, "Invalid integer type.");
    static_assert(!numeric_limits<FLOAT_TYPE>::is_integer, "Invalid float type.");
    static_assert(numeric_limits<FLOAT_TYPE>::has_infinity, "Invalid float type.");
    static_assert(numeric_limits<INT_TYPE>::radix == 2, "Implementation assumes radix 2.");
    PREC(NANConversion, f == f);
    PREC(InfinityConversion, f == numeric_limits<FLOAT_TYPE>::infinity());
    PREC(InfinityConversion, f == -numeric_limits<FLOAT_TYPE>::infinity());

    // Treat 0 specially
    if (f == 0.0) {
      m_content = part_list(1ull, 0);
    }

    union {
      INT_TYPE i;
      FLOAT_TYPE f;
    } result;
    result.f = f;

    // Get and set sign bit
    m_positive = result.i >> (MANTISSA + EXPONENT);

    // Extract exponent
    int64_t exponent = (result.i >> MANTISSA) & ((1 << EXPONENT) - 1);

    // Numbers smaller than 1 are just rounded to 0.
    if (exponent < BIAS) {
      m_content = part_list(1ull, 0);
      return;
    }

    // Take bias away and compensate for the size of the mantissa
    exponent -= BIAS + MANTISSA;

    // Extract mantissa and set hidden bit
    INT_TYPE mantissa = result.i & ((INT_TYPE(1) << MANTISSA) - 1);
    mantissa |= INT_TYPE(1) << MANTISSA;

    // Put into number
    for (uint_fast16_t i = 0; i < (sizeof(INT_TYPE) - 1) / sizeof(part_type) + 1; ++i) {
      m_content[i] = mantissa >> i * sizeof(part_type) * CHAR_BIT;
    }

    if (exponent > 0) {
      operator<<=(exponent);
    } else {
      operator>>=(-exponent);
    }
  }

  LongInt::LongInt(float initial)
  {
    convert_from<float, int32_t, FLOAT_MANTISSA, FLOAT_EXPONENT, FLOAT_BIAS>(initial);
  }

  LongInt::LongInt(double initial)
  {
    convert_from<double, int64_t, DOUBLE_MANTISSA, DOUBLE_EXPONENT, DOUBLE_BIAS>(initial);
  }

  LongInt::LongInt(long double initial):
    LongInt(double(initial))
  {
  }

  LongInt::LongInt(const string& numerical_string)
  {
    PREC(NoDigits, !numerical_string.empty());
    size_type length = numerical_string.length();
    size_type start_index = read_sign(numerical_string);
    arithmetic_assert(start_index <= length);
    PREC(NoDigits, start_index < length);
    if (numerical_string.find(HEXADECIMAL_BASE, start_index) == start_index) {
      start_index += HEXADECIMAL_BASE.length();
      read_hexadecimal(numerical_string, start_index);
    } else if (numerical_string.find(OCTAL_BASE, start_index) == start_index && length > OCTAL_BASE.length()) {
      start_index += OCTAL_BASE.length();
      read_octal(numerical_string, start_index);
    } else {
      read_decimal(numerical_string, start_index);
    }
  }

  inline LongInt::size_type LongInt::read_sign(const string& numerical_string)
  {
    arithmetic_assert(numerical_string.size() >= 1);
    if (numerical_string[0] == '-') {
      m_positive = false;
      return 1;
    } else if (numerical_string[1] == '+') {
      m_positive = true;
      return 1;
    } else {
      m_positive = true;
      return 0;
    }
  }

  inline void LongInt::read_decimal(const string& numerical_string, size_type start_index)
  {
    bool positive = m_positive;
    m_positive = true;
    m_content = part_list(1ull, 0);
    PREC(NoDigits, start_index < numerical_string.length());

    for (string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      PREC(InvalidDigit, *it >= '0' && *it <= '9');
    }
    unsigned int i;
    for (i = start_index; i + DECIMAL_BUFFER_SIZE < numerical_string.length(); i += DECIMAL_BUFFER_SIZE) {
      operator*=(TEN_BUFFER_FACTOR);
      istringstream iss (numerical_string.substr(i, DECIMAL_BUFFER_SIZE));
      part_type part;
      iss >> part;
      operator+=(part);
    }
    unsigned int rest_length = numerical_string.length() - i;
    if (rest_length > 0) {
      LongInt base_power (TEN);
      base_power.pow_eq(rest_length);
      operator*=(base_power);
      istringstream iss (numerical_string.substr(i, DECIMAL_BUFFER_SIZE));
      part_type part;
      iss >> part;
      operator+=(part);
    }
    m_positive = positive;
  }

  inline void LongInt::read_hexadecimal(const string& numerical_string, size_type start_index)
  {
    PREC(NoDigits, start_index < numerical_string.length());
    for (string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      PREC(InvalidDigit, (*it >= '0' && *it <= '9') || (*it >= 'A' && *it <= 'F') || (*it >= 'a' && *it <= 'f'));
    }
    size_type length = numerical_string.length() - start_index;
    size_type size = length / HEXADECIMAL_BUFFER_SIZE;
    if (size * HEXADECIMAL_BUFFER_SIZE < length) {
      ++size;
    }
    m_content = part_list(size, 0);
    size_type i = start_index + length;
    size_type j = 0;
    while (i > start_index + HEXADECIMAL_BUFFER_SIZE) {
      i -= HEXADECIMAL_BUFFER_SIZE;
      istringstream iss (numerical_string.substr(i, HEXADECIMAL_BUFFER_SIZE));
      iss >> hex >> m_content[j];
      ++j;
    }
    istringstream iss (numerical_string.substr(start_index, i - start_index));
    iss >> hex >> m_content[j];
  }

  inline void LongInt::read_octal(const string& numerical_string, size_type start_index)
  {
    arithmetic_assert(numerical_string.length() > start_index);
    for (string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      PREC(InvalidDigit, *it >= '0' || *it <= '8');
    }
    PREC(NotImplemented, false);
  }

  inline void LongInt::write_decimal(ostream& out) const
  {
    LongInt longInt (abs());
    ArrayList<string> parts;
    longInt.m_positive = true;
    while (longInt > ZERO) {
      ostringstream s;
      LongInt remainder;
      longInt.divide(TEN_BUFFER_FACTOR, longInt, remainder, true);
      s << remainder.m_content[0];
      parts.push_back(s.str());
      if (longInt > ZERO) {
        arithmetic_assert(DECIMAL_BUFFER_SIZE >= s.str().length());
        for (unsigned int j = 0; j < DECIMAL_BUFFER_SIZE - s.str().length(); ++j) {
          parts.push_back("0");
        }
      }
    }
    if (parts.empty()) {
      out << "0";
    }
    while (!parts.empty()) {
      out << parts.pop_back();
    }
  }

  inline void LongInt::write_octal(ostream& out) const
  {
    PREC(NotImplemented, false);
  }

  inline void LongInt::write_hexadecimal(ostream& out) const
  {
    for (size_type i = m_content.size(); i > 0;) {
      --i;
      ostringstream oss;
      oss.flags(ios_base::hex);
      oss << m_content[i];
      if (i < m_content.size() - 1) {
        for (uint_fast16_t j = oss.str().size(); j < sizeof(part_type) * 2; ++j) {
          out << '0';
        }
      }
      out << oss.str();
      oss.flush();
    }
  }

  LongInt::operator bool() const
  {
    return operator!=(ZERO);
  }

  LongInt::operator char() const {
    return m_positive ? m_content[0] : -m_content[0];
  }

  LongInt::operator unsigned char() const {
    return m_content[0];
  }

  LongInt::operator short int() const {
    return m_positive ? m_content[0] : -m_content[0];
  }

  LongInt::operator unsigned short int() const {
    return m_content[0];
  }

  LongInt::operator int() const {
    return m_positive ? m_content[0] : -m_content[0];
  }

  LongInt::operator unsigned int() const {
    return m_content[0];
  }

  LongInt::operator long int() const {
    return m_positive ? m_content[0] : -m_content[0];
  }

  LongInt::operator unsigned long int() const {
    return m_content[0];
  }

  LongInt::operator long long int() const {
    return m_positive ? m_content[0] : -m_content[0];
  }

  LongInt::operator unsigned long long int() const {
    return m_content[0];
  }

  template <typename FLOAT_TYPE, typename INT_TYPE, int MANTISSA, int EXPONENT, int BIAS>
  inline FLOAT_TYPE LongInt::convert_to() const
  {
    static_assert(sizeof(INT_TYPE) == sizeof(FLOAT_TYPE), "Incompatible sizes.");
    static_assert(MANTISSA + EXPONENT + 1 == CHAR_BIT * sizeof(FLOAT_TYPE), "Invalid exponent or mantissa size.");
    static_assert(numeric_limits<INT_TYPE>::is_integer, "Invalid integer type.");
    static_assert(!numeric_limits<FLOAT_TYPE>::is_integer, "Invalid float type.");
    static_assert(numeric_limits<FLOAT_TYPE>::has_infinity, "Invalid float type.");
    static_assert(numeric_limits<INT_TYPE>::radix == 2, "Implementation assumes radix 2.");
    // Treat 0 specially
    if (operator==(ZERO)) {
      return 0.0;
    }

    union {
      INT_TYPE i;
      FLOAT_TYPE f;
    } result;

    // Take fist digit
    part_type first_digit = m_content[size() - 1];
    size_type exponent = log2(first_digit);

    // If our first digit is already too large, truncate.
    if (exponent > MANTISSA) {
      first_digit >>= exponent - MANTISSA;
    }

    // Now it is guaranteed to fit.
    result.i = first_digit;

    // If there is space for more digits
    if (exponent < MANTISSA) {
      result.i <<= MANTISSA - exponent;
      // Take as many digits as fit into the mantissa and as many as we have.
      // Note that the for loop gets executed at most constantly many times since MANTISSA is a constant,
      // so the compiler will probably unroll it.
      for (uint_fast16_t i = 0; size() > i + 2 && MANTISSA > exponent + i * sizeof(part_type); ++i) {
        // Insert the part at the right position, in the last step, this might be a right shift
        result.i |= m_content[size() - i - 2] << (MANTISSA - exponent - (i + 1) * sizeof(part_type));
      }
    }

    // Cut out leading bit
    result.i &= (INT_TYPE(1) << MANTISSA) - 1;
    exponent += (size() - 1) * sizeof(part_type) * CHAR_BIT + BIAS;
    if (exponent >= 1 << EXPONENT) {
      // Special case: Infinity
      if (m_positive) {
        return numeric_limits<FLOAT_TYPE>::infinity();
      } else {
        return -numeric_limits<FLOAT_TYPE>::infinity();
      }
    } else {
      // Set exponent
      result.i |= exponent << MANTISSA;
    }
    if (!m_positive) {
      result.i |= INT_TYPE(1) << (MANTISSA + EXPONENT);
    }
    return result.f;
  }

  LongInt::operator float() const
  {
    return convert_to<float, int32_t, FLOAT_MANTISSA, FLOAT_EXPONENT, FLOAT_BIAS>();
  }

  LongInt::operator double() const
  {
    return convert_to<double, int64_t, DOUBLE_MANTISSA, DOUBLE_EXPONENT, DOUBLE_BIAS>();
  }

  LongInt::operator long double() const
  {
    return operator double();
  }

  LongInt LongInt::operator~() const
  {
    return --operator-();
  }

  LongInt LongInt::operator-() const
  {
    if (operator==(ZERO)) {
      return *this;
    } else {
      LongInt result(*this);
      result.m_positive = !m_positive;
      return result;
    }
  }

  LongInt LongInt::operator+() const
  {
    return *this;
  }

  LongInt LongInt::operator+(const LongInt& other) const
  {
    LongInt result(*this);
    return result += other;
  }

  LongInt LongInt::operator-(const LongInt& other) const
  {
    LongInt result(*this);
    return result -= other;
  }

  LongInt LongInt::operator*(const LongInt& other) const
  {
    LongInt result(*this);
    return result *= other;
  }

  LongInt LongInt::operator/(const LongInt& other) const
  {
    LongInt result(*this);
    return result /= other;
  }

  LongInt LongInt::operator%(const LongInt& other) const
  {
    LongInt result(*this);
    return result %= other;
  }

  LongInt LongInt::mod(const LongInt &modulus) const
  {
    LongInt result (*this);
    return result.mod_eq(modulus);
  }

  LongInt LongInt::operator<<(exponent_type shift_offset) const
  {
    LongInt result(*this);
    return result <<= shift_offset;
  }

  LongInt LongInt::operator>>(exponent_type shift_offset) const
  {
    LongInt result(*this);
    return result >>= shift_offset;
  }

  LongInt LongInt::pow(exponent_type exponent) const
  {
    LongInt result(*this);
    return result.pow_eq(exponent);
  }

  LongInt LongInt::pow_mod(const LongInt& exponent, const LongInt& modulus) const
  {
    LongInt result(*this);
    return result.pow_mod_eq(exponent, modulus);
  }

  LongInt LongInt::operator|(const LongInt& other) const
  {
    LongInt result(*this);
    return result |= other;
  }

  LongInt LongInt::operator^(const LongInt& other) const
  {
    LongInt result(*this);
    return result ^= other;
  }

  LongInt LongInt::operator&(const LongInt& other) const
  {
    LongInt result(*this);
    return result &= other;
  }

  LongInt LongInt::operator++(int)
  {
    LongInt result (*this);
    operator++();
    return result;
  }

  LongInt& LongInt::operator++()
  {
    return operator+=(ONE);
//    if (!m_positive && size() == 1 && m_content[0] == 1) {
//      m_content[0] = 0;
//      m_positive = true;
//    } else if (m_positive) {
//      inc();
//    } else {
//      dec();
//    }
//    return *this;
  }

  // Increments without looking at the sign
  void inline LongInt::inc()
  {
    bool keep = true;
    for (ArrayList<part_type>::iterator it = m_content.begin(); keep; ++it) {
      if (it >= m_content.end()) {
        m_content.push_back(0);
      }
      asm("incq %0;\n"
      "\tsetc %1;"
      : "=q" (*it), "=q" (keep) : "0" (*it), "1" (keep));
    }
  }

  LongInt LongInt::operator--(int)
  {
    LongInt result (*this);
    operator--();
    return result;
  }

  LongInt& LongInt::operator--()
  {
    return operator-=(ONE);
//    if (size() == 1 && m_content[0] == 0) {
//      m_content[0] = 1;
//      m_positive = false;
//    } else if (m_positive) {
//      dec();
//    } else {
//      inc();
//    }
//    return *this;
  }

  // Decrements without looking at the sign
  void inline LongInt::dec()
  {
    bool keep = true;
    for (ArrayList<part_type>::iterator it = m_content.begin(); keep; ++it) {
      if (it >= m_content.end()) {
        m_content.push_back(0);
      }
      asm("decq %0;\n"
      "\tsetc %1;"
      : "=q" (*it), "=q" (keep) : "0" (*it), "1" (keep));
    }
  }

  int_fast8_t LongInt::compare_to(const LongInt& other) const
  {
    if (m_positive) {
      if (!other.m_positive) {
        return 1;
      } else {
        return u_compare_to(other);
      }
    } else {
      if (other.m_positive) {
        return -1;
      } else {
        return -u_compare_to(other);
      }
    }
  }

  LongInt& LongInt::operator+=(const LongInt& other)
  {
    if (other.m_positive != m_positive) {
      subtract(other);
    } else {
      add(other);
    }
    return *this;
  }

  // Treat other number as same sign
  void inline LongInt::add(const LongInt &other)
  {
    pad_zeros(max(size(), other.size()) + 1);
    DataStructures::add(&m_content[0],
                        &m_content[0] + size(),
                        &other.m_content[0],
                        &other.m_content[0] + other.size());
    remove_zeros();
  }

  void LongInt::pad_zeros(size_type new_size)
  {
    for (size_type i = size(); i < new_size; ++i) {
      m_content.push_back(0ul);
    }
  }

  LongInt& LongInt::operator-=(const LongInt& other)
  {
    if (other.m_positive != m_positive) {
      add(other);
    } else {
      subtract(other);
    }
    return *this;
  }

  // Treat other number as same sign
  void inline LongInt::subtract(const LongInt &other)
  {
    if (u_compare_to(other) == -1) {
      pad_zeros(other.size());
      DataStructures::subtract(&m_content[0],
                               &m_content[0] + size(),
                               &other.m_content[0],
                               &other.m_content[0] + other.size(),
                               true);
      m_positive = !m_positive;
    } else {
      DataStructures::subtract(&m_content[0],
                               &m_content[0] + size(),
                               &other.m_content[0],
                               &other.m_content[0] + other.size(),
                               false);
    }
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
  }

  LongInt& LongInt::operator*=(const LongInt& other)
  {
    size_type space = space_usage(size(), other.size());
    part_type *c = (part_type*)malloc(space * sizeof(part_type));
    part_type *c_end = multiply(&m_content[0],
                                &m_content[0] + size(),
                                &other.m_content[0],
                                &other.m_content[0] + other.size(),
                                c,
                                c + space);
    m_content.clear();
    m_content.insert(m_content.end(), c, c_end);
    free(c);
    m_positive = m_positive == other.m_positive;
    if (size() == 0) {
      m_content.push_back(0);
      m_positive = true;
    }
    remove_zeros();
    return *this;
  }

  LongInt& LongInt::operator/=(const LongInt& other)
  {
    LongInt remainder;
    divide(other, *this, remainder, false);
    return *this;
  }

  LongInt& LongInt::operator%=(const LongInt& other)
  {
    LongInt quotient;
    divide(other, quotient, *this, true);
    return *this;
  }

  // Difference to %= is the sign handling
  LongInt& LongInt::mod_eq(const LongInt& other)
  {
    LongInt quotient;
    divide(other, quotient, *this, true);
    if (m_positive != other.m_positive) {
      operator+=(other);
    }
    return *this;
  }

  // Note that it is not a problem, if the quotient or remainder is the same as *this because
  // *this gets copied and scaled first.
  void LongInt::divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed)
  {
    bool positive = m_positive;
    bool other_positive = other.m_positive;
    LongInt dividend (abs());
    LongInt divisor (other.abs());
    LongArithmetic::divide(dividend, divisor, quotient, remainder, remainder_needed);
    if (remainder_needed) {
      if (remainder != ZERO) {
        remainder.m_positive = positive;
      }
    }
    if (quotient != ZERO) {
      quotient.m_positive = positive == other_positive;
    }
  }

  LongInt& LongInt::operator<<=(exponent_type shift_offset)
  {
    if (shift_offset < 0) {
      PREC(NegationOverflow, shift_offset != -shift_offset);
      return operator <<=(-shift_offset);
    }
    size_type per_part_shift = shift_offset % PART_SIZE;
    size_type part_shift = shift_offset / PART_SIZE;
    if (per_part_shift != 0) {
      part_type keep = 0;
      for (size_type i = 0; keep != 0 || i < size(); ++i) {
        if (i >= size()) {
          m_content.push_back(0);
        }
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[i] << per_part_shift) | keep;
        keep = m_content[i] >> (PART_SIZE - per_part_shift);
        m_content[i] = shifted;
      }
    }
    if (part_shift > 0) {
      m_content.insert(0, part_shift, 0);
    }
    return *this;
  }

  LongInt& LongInt::operator>>=(exponent_type shift_offset)
  {
    if (shift_offset < 0) {
      PREC(NegationOverflow, shift_offset != -shift_offset);
      return operator <<=(-shift_offset);
    }
    // Necessary because this could lead to an invalid index while calculating the correction bit in our implementation.
    if (shift_offset == 0) {
      return *this;
    }
    size_type per_part_shift = shift_offset % PART_SIZE;
    size_type part_shift = shift_offset / PART_SIZE;
    // Handle the case that the number completely disappears, this resolves nasty two complements handling for negative numbers.
    if (part_shift >= size() || (part_shift + 1 == size() && (m_content[part_shift] >> per_part_shift) == 0)) {
      return operator=(m_positive ? ZERO : MINUS_ONE);
    }
    // Correction for negative numbers because of two complement semantic
    bool extra_bit = false;
    if (!m_positive) {
      // Check if a bit whose whole part gets shifted away is 1
      for (size_type i = 0; i < part_shift && !extra_bit; ++i) {
        extra_bit = m_content[i] != 0;
      }
      // Check if a bit in the part that gets shifted away partially is 1
      extra_bit = extra_bit || (((m_content[part_shift] >> per_part_shift) << per_part_shift) != m_content[part_shift]);
    }
    if (per_part_shift > 0) {
      part_type keep = 0;
      size_type j = size();
      // The strange for loop is necessary because of the unsigned types.
      for (size_type i = 0; i < size(); ++i) {
        --j;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[j] >> per_part_shift) | keep;
        keep = m_content[j] << (PART_SIZE - per_part_shift);
        m_content[j] = shifted;
      }
    }
    if (part_shift > 0) {
      for (part_list::iterator it = m_content.begin(); it < m_content.end() - part_shift; ++it) {
        *it = it[part_shift];
      }
      for (size_type i = 0; i < part_shift; ++i) {
        m_content.pop_back();
      }
    }
    if (extra_bit) {
      // We know the sign is negative, so -- increments the content
      inc();
    }
    remove_zeros();
    return *this;
  }

  LongInt& LongInt::pow_eq(exponent_type exponent)
  {
    AlgebraHelper::pow_eq(&RING, *this, exponent);
    return *this;
  }

  LongInt& LongInt::pow_mod_eq(const LongInt& exponent, const LongInt& modulus)
  {
    AlgebraHelper::pow_mod_eq(&RING, *this, exponent, modulus);
    return *this;
  }

  LongInt& LongInt::operator|=(const LongInt& other)
  {
    bool new_positive = m_positive && other.m_positive;
    bool keep = !m_positive;
    bool other_keep = !other.m_positive;
    bool new_keep = !new_positive;
    for (size_type i = 0; i < max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part | other_part, new_keep);
      if (i >= size()) {
        m_content.push_back(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    arithmetic_assert(keep == 0 && other_keep == 0 && new_keep == 0);
    m_positive = new_positive;
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
    return *this;
  }

  LongInt& LongInt::operator^=(const LongInt& other)
  {
    bool new_positive = m_positive == other.m_positive;
    bool keep = !m_positive;
    bool other_keep = !other.m_positive;
    bool new_keep = !new_positive;
    for (size_type i = 0; i < max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part ^ other_part, new_keep);
      if (i >= size()) {
        m_content.push_back(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    arithmetic_assert(keep == 0 && other_keep == 0 && new_keep == 0);
    m_positive = new_positive;
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
    return *this;
  }

  LongInt& LongInt::operator&=(const LongInt& other)
  {
    bool new_positive = m_positive || other.m_positive;
    bool keep = !m_positive;
    bool other_keep = !other.m_positive;
    bool new_keep = !new_positive;
    for (size_type i = 0; i < max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part & other_part, new_keep);
      if (i >= size()) {
        m_content.push_back(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    arithmetic_assert(keep == 0 && other_keep == 0 && new_keep == 0);
    m_positive = new_positive;
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
    return *this;
  }

  LongInt LongInt::abs() const
  {
    return m_positive ? *this : operator-();
  }

  int_fast8_t LongInt::u_compare_to(const LongInt& other) const
  {
    if (this == &other) {
      return true;
    }
    size_type max_index = max(size(), other.size());
    for (size_type i = max_index + 1; i > 0;) {
      --i;
      part_type my = part_at(i);
      part_type his = other.part_at(i);
      if (my > his) {
        return 1;
      } else if (his > my) {
        return -1;
      }
    }
    return 0;
  }

  void LongInt::remove_zeros()
  {
    while (size() > 1 && m_content[size() - 1] == 0) {
      m_content.pop_back();
    }
  }

  LongInt LongInt::mult_inv_mod(const LongInt &modulus) const
  {
    PREC(InvalidModulus, modulus >= TWO);
    return AlgebraHelper::inv_mod(&RING, mod(modulus), modulus);
  }

  LongInt LongInt::add_inv_mod(const LongInt &modulus) const
  {
    return operator-().mod(modulus);
  }

  LongInt::size_type log2(const LongInt& number)
  {
    return (number.size() - 1) * LongInt::PART_SIZE + log2(number.m_content[number.size() - 1]);
  }

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, bool& keep)
  {
    if (positive) {
      return part;
    } else {
      part = ~part;
      if (keep) {
        ASM_INC_SETCF(part, keep);
      }
      return part;
    }
  }

}
