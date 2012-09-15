#include "longint.h"
#include "algebrahelper.h"
#include "multiply.h"
#include "divide.h"
#include "add.h"
#include "subtract.h"
#include "assembly.h"
#include "ring.h"
#include "shifts.h"
#include "compare.h"
#include "incdec.h"
#include "arithmetichelper.h"
#include "longintconverter.h"
#include <cmath>
#include <sstream>
#include <string>
#include <climits>
#include <cctype>

#define NIBBLE_BIT 4

namespace LongArithmetic {

  using namespace ArithmeticHelper;
  using namespace LongArithmetic;
  using namespace Operations;
  using namespace std;

  static const unsigned int DECIMAL_BUFFER_SIZE = (PART_SIZE * 1233) >> 12; // Calculates log_10(2^PART_SIZE)
  static const unsigned int OCTAL_BUFFER_SIZE = (PART_SIZE / 3); // Calculates log_8(2^PART_SIZE)

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
      longInt.write_hexadecimal_nosign(out);
    } else if (ff & ios_base::oct) {
      if (ff & ios_base::showbase) {
        out << OCTAL_BASE;
      }
      longInt.write_octal_nosign(out);
    } else {
      longInt.write_decimal_nosign(out);
    }
    return out;
  }

  istream& operator>>(istream& in, LongInt& longInt)
  {
    while (!in.eof() && !in.bad() && isspace(in.peek())) {
      in.get();
    }
    longInt.read_sign(in);
    longInt.read_nosign(in);
    return in;
  }

  void LongInt::read_nosign(istream& in)
  {
    ios_base::fmtflags ff = in.flags();
    if (ff & ios_base::hex) {
      read_hexadecimal_nosign(in);
    } else if (ff & ios_base::oct) {
      read_octal_nosign(in);
    } else {
      read_decimal_nosign(in);
    }
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
  {}

  LongInt::LongInt(const string& numerical_string)
  {
    PREC(NoDigits, !numerical_string.empty());
    istringstream iss (numerical_string);
    read_sign(iss);
    PREC(NoDigits, !iss.eof());
    PREC(NoDigits, !iss.fail());
    if (read_and_set_base(iss)) {
      m_content = part_list(size_type(1), 0);
      m_positive = true;
      return;
    }
    PREC(NoDigits, !iss.eof());
    PREC(NoDigits, !iss.fail());
    read_nosign(iss);
    PREC(NoDigits, !iss.fail());
    PREC(InvalidDigit, iss.eof());
  }

  // Returns true if it is just a simple zero
  inline bool LongInt::read_and_set_base(istream& in) const
  {
    if (in.bad() || in.eof()) {
      in.setstate(ios_base::failbit);
    } else if (in.peek() == '0') {
      in.get();
      if (in.bad()) {
        in.setstate(ios_base::failbit);
      } else if (in.eof()) {
        in.seekg(-1, ios_base::cur);
      } else if (in.peek() == 'x') {
        in.get();
        in.setf(ios_base::hex, ios_base::basefield);
      } else if ('0' <= in.peek() && in.peek() <= '7') {
        in.setf(ios_base::oct, ios_base::basefield);
      } else {
        // We have to treat this specially because we have already read the zero.
        return true;
      }
    } else {
      in.setf(ios_base::dec, ios_base::basefield);
    }
    return false;
  }

  inline bool LongInt::read_sign(istream& in)
  {
    if (in.peek() == '-') {
      m_positive = false;
      in.get();
    } else if (in.peek() == '+') {
      m_positive = true;
      in.get();
    } else {
      m_positive = true;
    }
    return m_positive;
  }

  inline void LongInt::read_decimal_nosign(istream& in)
  {
    // TODO Efficiency using hierarchical buffers
    bool positive = m_positive;
    m_positive = true; // We want the multiplications/additions to be unsigned
    m_content = part_list(size_type(1), 0);
    if (in.eof() || in.bad() || !isdigit(in.peek())) {
      in.setstate(ios_base::failbit);
      return;
    }
    size_type buffer_size = 0;
    part_type buffer = 0;
    while (!in.eof() && !in.bad() && isdigit(in.peek())) {
      char c = in.get() - '0';
      buffer *= 10;
      buffer += c;
      ++buffer_size;
      if (buffer_size == DECIMAL_BUFFER_SIZE) {
        operator*=(TEN_BUFFER_FACTOR);
        operator+=(buffer);
        buffer_size = 0;
        buffer = 0;
      }
    }
    if (buffer_size > 0) {
      LongInt base_power (TEN);
      base_power.pow_eq(buffer_size);
      operator*=(base_power);
      operator+=(buffer);
    }
    m_positive = positive;
  }

  inline void LongInt::read_hexadecimal_nosign(istream& in)
  {
    m_content = part_list(size_type(1), 0);
    if (in.eof() || in.bad() || !isxdigit(in.peek())) {
      m_positive = true;
      in.setstate(ios_base::failbit);
      return;
    }
    size_type buffer_size = 0;
    while (!in.eof() && !in.bad() && isxdigit(in.peek())) {
      if (buffer_size == PART_SIZE) {
        m_content.push_back(0);
        buffer_size = 0;
      }
      char c = in.get();
      m_content.back() <<= NIBBLE_BIT;
      if ('0' <= c && c <= '9') {
        m_content.back() += c - '0';
      } else if ('A' <= c && c <= 'F') {
        m_content.back() += c - 'A' + 10;
      } else if ('a' <= c && c <= 'f') {
        m_content.back() += c - 'a' + 10;
      } else {
        assert(false);
      }
      buffer_size += NIBBLE_BIT;
    }
    // Shift such that the buffer gap is at the beginning.
    m_content.back() <<= PART_SIZE - buffer_size;
    // Reverse parts
    for (size_type i = 0; i < m_content.size() / 2; ++i) {
      std::swap(m_content[i], m_content[m_content.size() - 1 - i]);
    }
    // Shift away remaining buffer size
    operator>>=(PART_SIZE - buffer_size);
  }

  inline void LongInt::read_octal_nosign(istream& in)
  {
    PREC(NotImplemented, false);
  }

  inline void LongInt::write_decimal_nosign(ostream& out) const
  {
    LongInt longInt (abs());
    DataStructures::ArrayList<string> parts;
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

  inline void LongInt::write_octal_nosign(ostream& out) const
  {
    PREC(NotImplemented, false);
  }

  inline void LongInt::write_hexadecimal_nosign(ostream& out) const
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
    if (!m_positive && size() == 1 && m_content[0] == 1) {
      m_content[0] = 0;
      m_positive = true;
    } else if (m_positive) {
      inc();
    } else {
      dec();
    }
    return *this;
  }

  // Increments without looking at the sign
  void inline LongInt::inc()
  {
    bool keep = Operations::inc(&m_content[0], &m_content[0] + size());
    if (keep) {
      m_content.push_back(1);
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
    if (size() == 1 && m_content[0] == 0) {
      m_content[0] = 1;
      m_positive = false;
    } else if (m_positive) {
      dec();
    } else {
      inc();
    }
    return *this;
  }

  // Decrements without looking at the sign
  void inline LongInt::dec()
  {
    Operations::dec(&m_content[0], &m_content[0] + size());
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
    arithmetic_assert(size() > 0);
    pad_zeros(max(size(), other.size()) + 1);
    Operations::add(&m_content[0],
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
    arithmetic_assert(size() > 0);
    if (u_compare_to(other) == -1) {
      pad_zeros(other.size());
      Operations::subtract(&m_content[0],
                           &m_content[0] + size(),
                           &other.m_content[0],
                           &other.m_content[0] + other.size(),
                           true);
      m_positive = !m_positive;
    } else {
      Operations::subtract(&m_content[0],
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
    arithmetic_assert(size() > 0);
    size_type space = space_usage(size(), other.size());
    part_type *c_begin = static_cast<part_type*>(malloc(space * sizeof(part_type)));
    part_type *c_end = multiply(&m_content[0],
                                &m_content[0] + size(),
                                &other.m_content[0],
                                &other.m_content[0] + other.size(),
                                c_begin,
                                c_begin + space);
    // Remove padding
    while (c_end > c_begin + 1 && c_end[-1] == 0) {
      --c_end;
    }
    m_content.clear();
    m_content.insert(m_content.end(), c_begin, c_end);
    free(c_begin);
    m_positive = m_positive == other.m_positive;
    // Zero results in an empty result. Correct this.
    if (size() == 0) {
      m_content.push_back(0);
      m_positive = true;
    }
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
    Operations::divide(dividend, divisor, quotient, remainder, remainder_needed);
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
      return operator<<=(-shift_offset);
    }
    size_type per_part_shift = shift_offset % PART_SIZE;
    size_type part_shift = shift_offset / PART_SIZE;
    if (per_part_shift != 0) {
      part_type keep = shift_left(&m_content[0], &m_content[0] + size(), per_part_shift);
      if (keep != 0) {
        m_content.push_back(keep);
      }
    }
    if (part_shift > 0) {
      m_content.insert(m_content.begin(), part_shift, 0);
    }
    return *this;
  }

  LongInt& LongInt::operator>>=(exponent_type shift_offset)
  {
    if (shift_offset < 0) {
      PREC(NegationOverflow, shift_offset != -shift_offset);
      return operator<<=(-shift_offset);
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
    if (part_shift > 0) {
      arithmetic_assert(part_shift < size() - 1);
      m_content.erase(m_content.begin(), m_content.begin() + part_shift);
    }
    if (per_part_shift > 0) {
      shift_right(&m_content[0], &m_content[0] + m_content.size(), per_part_shift);
    }
    remove_zeros();
    if (extra_bit) {
      // TODO We know the sign is negative, so -- increments the content
      operator--();
    }
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
      return 0;
    }
    return Operations::compare_to(&m_content[0],
                                  &m_content[0] + size(),
                                  &other.m_content[0],
                                  &other.m_content[0] + other.size());
  }

  void LongInt::remove_zeros()
  {
    while (m_content.size() > 1 && m_content[size() - 1] == 0) {
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

  LongInt operator "" _long(const char * literal_string)
  {
    return LongInt(string(literal_string));
  }

  LongInt::size_type log2(const LongInt& number)
  {
    return (number.size() - 1) * PART_SIZE + log2(number.m_content[number.size() - 1]);
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
