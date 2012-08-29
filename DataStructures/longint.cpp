#include "longint.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include "arithmetichelper.h"

namespace DataStructures {

  using namespace ArithmeticHelper;

  static const unsigned int DECIMAL_BUFFER_SIZE = (LongInt::PART_SIZE * 1233) >> 12; // Calculates log_10(2^PART_SIZE)
  static const unsigned int HEXADECIMAL_BUFFER_SIZE = (LongInt::PART_SIZE / 4); // Calculates log_16(2^PART_SIZE)
  static const unsigned int OCTAL_BUFFER_SIZE = (LongInt::PART_SIZE / 3); // Calculates log_8(2^PART_SIZE)

  static const std::string HEXADECIMAL_BASE = "0x";
  static const std::string OCTAL_BASE = "0";

  static const LongInt TEN (10);
  static const LongInt ZERO (0);
  static const LongInt ONE (1);
  static const LongInt TWO (2);
  static const LongInt MINUS_ONE (-1);

  static const LongInt TEN_BUFFER_FACTOR (TEN.pow(DECIMAL_BUFFER_SIZE));

  static const index_type base (10);

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt)
  {
    std::ios_base::fmtflags ff = out.flags();
    if (!longInt.m_positive) {
      out << "-";
    } else if (ff & std::ios_base::showpos) {
      out << "+";
    }
    if (longInt.size() == 1) {
      out << longInt.m_content[0];
    } else if (ff & std::ios_base::hex) {
      if (ff & std::ios_base::showbase) {
        out << HEXADECIMAL_BASE;
      }
      longInt.write_hexadecimal(out);
    } else if (ff & std::ios_base::oct) {
      if (ff & std::ios_base::showbase) {
        out << OCTAL_BASE;
      }
      longInt.write_octal(out);
    } else {
      longInt.write_decimal(out);
    }
    return out;
  }

  std::istream& operator>>(std::istream& in, LongInt& longInt)
  {
    std::ios_base::fmtflags ff = in.flags();
    std::string s;
    in >> s;
    index_type length = s.length();
    index_type start_index = longInt.read_sign(s);
    assert(start_index <= length);
    if (start_index == length) {
      throw std::logic_error("Numerical string without digits is not allowed.");
    }
    if (ff & std::ios_base::hex) {
      longInt.read_hexadecimal(s, start_index);
    } else if (ff & std::ios_base::oct) {
      longInt.read_octal(s, start_index);
    } else {
      longInt.read_decimal(s, start_index);
    }
    return in;
  }

  LongInt::LongInt():
    m_positive (true)
  {
    m_content.push(0);
  }

  LongInt::LongInt(long long int initial):
    m_positive (initial >= 0)
  {
    m_content.push(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned long long int initial):
    m_positive (true)
  {
    m_content.push(initial);
  }

  LongInt::LongInt(long int initial):
    m_positive (initial >= 0)
  {
    m_content.push(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned long int initial):
    m_positive (true)
  {
    m_content.push(initial);
  }

  LongInt::LongInt(int initial):
    m_positive (initial >= 0)
  {
    m_content.push(m_positive ? initial : -initial);
  }

  LongInt::LongInt(unsigned int initial):
    m_positive (true)
  {
    m_content.push(initial);
  }

  LongInt::LongInt(const packed_longint_t& packed):
    m_positive (packed.sign),
    m_content (packed.num_parts / 2 + packed.num_parts % 2, 0)
  {
    index_type i = 0;
    for (; i < packed.num_parts / 2; ++i) {
      assert(i < size());
      m_content[i] = packed.parts[2 * i] + (part_type(packed.parts[2 * i + 1]) << (PART_SIZE / 2));
    }
    if (2 * i < packed.num_parts) {
      assert(i < size());
      m_content[i] = packed.parts[2 * i];
    }
    remove_zeros();
  }

  LongInt::LongInt(const u_int8_t* parts, index_type length):
    m_positive (true),
    m_content (length / sizeof(part_type) + 1, 0)
  {
    for (index_type i = 0; i < length; ++i) {
      part_type c = parts[i];
      m_content[i / sizeof(part_type)] |= c << CHAR_BIT * (i % sizeof(part_type));
    }
    remove_zeros();
  }

  LongInt::LongInt(const std::string& numerical_string)
  {
    if (numerical_string.empty()) {
      throw std::logic_error("Empty numerical string is not allowed.");
    }
    index_type length = numerical_string.length();
    index_type start_index = read_sign(numerical_string);
    assert(start_index <= length);
    if (start_index == length) {
      throw std::logic_error("Numerical string without digits is not allowed.");
    }
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

  inline index_type LongInt::read_sign(const std::string& numerical_string)
  {
    assert(numerical_string.size() >= 1);
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

  inline void LongInt::read_decimal(const std::string& numerical_string, index_type start_index)
  {
    bool positive = m_positive;
    m_positive = true;
    if (start_index == numerical_string.length()) {
      throw std::logic_error("Numerical string without digits is not allowed.");
    }
    for (std::string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      if (*it > '9' || *it < '0') {
        throw std::logic_error("Non digit in numerical string.");
      }
    }
    unsigned int i;
    for (i = start_index; i + DECIMAL_BUFFER_SIZE < numerical_string.length(); i += DECIMAL_BUFFER_SIZE) {
      operator*=(TEN_BUFFER_FACTOR);
      std::istringstream iss (numerical_string.substr(i, DECIMAL_BUFFER_SIZE));
      part_type part;
      iss >> part;
      operator+=(part);
    }
    unsigned int rest_length = numerical_string.length() - i;
    if (rest_length > 0) {
      LongInt base_power (TEN);
      base_power.pow_eq(rest_length);
      operator*=(base_power);
      std::istringstream iss (numerical_string.substr(i, DECIMAL_BUFFER_SIZE));
      part_type part;
      iss >> part;
      operator+=(part);
    }
    m_positive = positive;
  }

  inline void LongInt::read_hexadecimal(const std::string& numerical_string, index_type start_index)
  {
    if (start_index == numerical_string.length()) {
      throw std::logic_error("Numerical string without digits is not allowed.");
    }
    for (std::string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      if ((*it > '9' || *it < '0') && (*it > 'F' || *it < 'A') && (*it > 'f' || *it < 'a')) {
        throw std::logic_error("Non digit in numerical string.");
      }
    }
    index_type length = numerical_string.length() - start_index;
    index_type size = length / HEXADECIMAL_BUFFER_SIZE;
    if (size * HEXADECIMAL_BUFFER_SIZE < length) {
      ++size;
    }
    m_content = ArrayList<part_type>(size, 0);
    index_type i = start_index + length;
    index_type j = 0;
    while (i > start_index + HEXADECIMAL_BUFFER_SIZE) {
      i -= HEXADECIMAL_BUFFER_SIZE;
      std::istringstream iss (numerical_string.substr(i, HEXADECIMAL_BUFFER_SIZE));
      iss >> std::hex >> m_content[j];
      ++j;
    }
    std::istringstream iss (numerical_string.substr(start_index, i - start_index));
    iss >> std::hex >> m_content[j];
  }

  inline void LongInt::read_octal(const std::string& numerical_string, index_type start_index)
  {
    assert(numerical_string.length() > start_index);
    for (std::string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      if (*it > '9' || *it < '0') {
        throw std::logic_error("Non digit in numerical string.");
      }
    }
    throw std::logic_error("Octal is not implemented yet.");
  }

  inline void LongInt::write_decimal(std::ostream& out) const
  {
    LongInt longInt (abs());
    ArrayList<std::string> parts;
    longInt.m_positive = true;
    while (longInt > ZERO) {
      std::ostringstream s;
      LongInt remainder;
      longInt.divide(TEN_BUFFER_FACTOR, longInt, remainder, true);
      s << remainder.m_content[0];
      parts.push(s.str());
      if (longInt > ZERO) {
        assert(DECIMAL_BUFFER_SIZE >= s.str().length());
        for (unsigned int j = 0; j < DECIMAL_BUFFER_SIZE - s.str().length(); ++j) {
          parts.push("0");
        }
      }
    }
    if (parts.is_empty()) {
      out << "0";
    }
    while (!parts.is_empty()) {
      out << parts.pop();
    }
  }

  index_type LongInt::write(u_int8_t* dest) const throw()
  {
    for (index_type i = 0; i < size() - 1; ++i) {
      for (uint j = 0; j < sizeof(part_type); ++j) {
        dest[sizeof(part_type) * i + j] = (m_content[i] >> j * sizeof(part_type)) & 0xFF;
      }
    }
    index_type length = sizeof(part_type) * (size() - 1);
    part_type first_digit = m_content[size() - 1];
    for (; first_digit != 0; first_digit >>= sizeof(part_type), ++length) {
      dest[length] = first_digit & 0xFF;
    }
    return length;
  }

  inline void LongInt::write_octal(std::ostream& out) const
  {
    throw std::logic_error("Octal is not implemented yet.");
  }

  inline void LongInt::write_hexadecimal(std::ostream& out) const
  {
    for (index_type i = m_content.size(); i > 0;) {
      --i;
      out << std::hex << m_content[i];
    }
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

  LongInt LongInt::operator<<(index_type shift_offset) const
  {
    LongInt result(*this);
    return result <<= shift_offset;
  }

  LongInt LongInt::operator>>(index_type shift_offset) const
  {
    LongInt result(*this);
    return result >>= shift_offset;
  }

  LongInt LongInt::pow(index_type exponent) const
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
  }

  int LongInt::compareTo(const LongInt& other) const
  {
    if (m_positive) {
      if (!other.m_positive) {
        return 1;
      } else {
        return uCompareTo(other);
      }
    } else {
      if (other.m_positive) {
        return -1;
      } else {
        return -uCompareTo(other);
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
    pad_zeros(std::max(size(), other.size()) + 1);
    DataStructures::add(m_content.begin(), m_content.end(), other.m_content.begin(), other.m_content.end());
    remove_zeros();
  }

  inline void LongInt::pad_zeros(index_type new_size)
  {
    for (index_type i = size(); i < new_size; ++i) {
      m_content.push(0ul);
    }
    assert(size() >= new_size);
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
    if (uCompareTo(other) == -1) {
      pad_zeros(other.size());
      DataStructures::subtract(m_content.begin(), m_content.end(), other.m_content.begin(), other.m_content.end(), true);
      m_positive = !m_positive;
    } else {
      DataStructures::subtract(m_content.begin(), m_content.end(), other.m_content.begin(), other.m_content.end());
    }
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
  }

  LongInt& LongInt::operator*=(const LongInt& other)
  {
    ArrayList<part_type> c (space_usage(size(), other.size()));
    ArrayList<part_type>::const_iterator c_end = multiply(m_content.begin(), m_content.end(), other.m_content.begin(), other.m_content.end(), c.begin(), c.end());
    ArrayList<part_type>::const_iterator c_begin = c.begin();
    m_content.clear();
    m_content.push_all(c_begin, c_end);
    m_positive = m_positive == other.m_positive;
    if (size() == 0) {
      m_content.push(0);
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
    assert(other.part_at(other.size() - 1) != 0);
    LongInt quotient;
    divide(other, quotient, *this, true);
    return *this;
  }

  // Note that it is not a problem, if the quotient or remainder is the same as *this because
  // *this gets copied and scaled first.
  void LongInt::divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed)
  {
    if (uCompareTo(other) == -1) {
      if (remainder_needed) {
        remainder = *this;
      }
      quotient = ZERO;
      return;
    }
    bool positive = m_positive;
    bool other_positive = other.m_positive;
    if (other == ZERO) {
      throw std::logic_error("Division by zero.");
    }
    // Maximal factor we can multiply the divisor with without increasing its size.
    part_type scale_factor = 1;
    part_type other_last_digit = other.m_content.end()[-1];
    assert(other_last_digit != 0);
    if (other_last_digit + 1 != 0) {
      // (1 << 64) / (other_last_digit + 1)
      asm("movq $0x1, %%rdx;\n"
      "\txorq %%rax, %%rax;\n"
      "\tdiv %1;"
      : "=a" (scale_factor) : "c" (other_last_digit + 1) : "rdx");
    }
    // This scaling does not change the result because it crosses out,
    // but it ensures that the first digit of the divisor is at least 1 << 63.
    LongInt dividend (abs());
    LongInt divisor (other.abs());
    if (scale_factor > 1) {
      LongInt scale = scale_factor;
      dividend *= scale;
      divisor *= scale;
    }
    part_type divisor_first_digit = divisor.m_content.end()[-1];
    assert(divisor_first_digit >= (1ul << 63));
    index_type divisor_size = divisor.size();
    assert(divisor_size == other.size());
    index_type i = dividend.size();
    // Initialize the results
    quotient = ZERO;
    remainder = ZERO;
    // Strange for loop necessary because of unsigned types.
    for (index_type i2 = 0; i2 < dividend.size(); ++i2) {
      --i;
      remainder <<= PART_SIZE;
      remainder += dividend.m_content[i];
      if (remainder.size() >= divisor_size) {
        // Guess according to the first one or two parts of the active part and the first digit of the divisor,
        // how many times the divisor fits into the active part. This guess can never be to high and because
        // of our scaling factor, it can be at most 2 to low (according to a proof of Knuth)
        part_type guess;
        asm("div %3;"
        : "=a" (guess) : "d" (remainder.part_at(divisor_size)), "a" (remainder.m_content[divisor_size - 1]), "q" (divisor_first_digit));
        LongInt back_calculated (divisor * LongInt(guess));
#ifndef NDEBUG
        index_type old_guess = guess;
#endif
        while (back_calculated > remainder) {
          back_calculated -= divisor;
          --guess;
        }
        assert(old_guess >= guess);
        assert(back_calculated + divisor > remainder);
        assert(old_guess - guess <= 2);
        remainder -= back_calculated;
        quotient.pad_zeros(i + 1);
        quotient.m_content[i] = guess;
      }
    }
    if (remainder_needed) {
      if (scale_factor != 1) {
        // We have to take back the scale_factor
        part_type upper = 0, lower = 0;
        LongInt old_remainder (remainder);
        remainder = ZERO;
        index_type i = old_remainder.size();
        for (index_type i2 = 0; i2 < old_remainder.size(); ++i2) {
          --i;
          lower = old_remainder.m_content[i];
          remainder.pad_zeros(i + 1);
          // upper:lower / scale_factor, store remainder into upper
          asm("div %2;"
          : "=a" (remainder.m_content[i]), "=d" (upper) : "q" (scale_factor), "a" (lower), "d" (upper));
        }
        // The division has to work without remainder
        assert(upper == 0);
      }
      remainder.remove_zeros();
      if (remainder != ZERO) {
        remainder.m_positive = positive;
      }
    }
    quotient.remove_zeros();
    if (quotient != ZERO) {
      quotient.m_positive = positive == other_positive;
    }
  }

  LongInt& LongInt::operator<<=(index_type shift_offset)
  {
    index_type per_part_shift = shift_offset % PART_SIZE;
    index_type part_shift = shift_offset / PART_SIZE;
    if (per_part_shift != 0) {
      part_type keep = 0;
      for (index_type i = 0; keep != 0 || i < size(); ++i) {
        if (i >= size()) {
          m_content.push(0);
        }
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[i] << per_part_shift) | keep;
        keep = m_content[i] >> (PART_SIZE - per_part_shift);
        m_content[i] = shifted;
      }
    }
    if (part_shift > 0) {
      m_content = ArrayList<part_type> (part_shift, 0) + m_content;
    }
    return *this;
  }

  LongInt& LongInt::operator>>=(index_type shift_offset)
  {
    // Necessary because this could lead to an invalid index while calculating the correction bit in our implementation.
    if (shift_offset == 0) {
      return *this;
    }
    index_type per_part_shift = shift_offset % PART_SIZE;
    index_type part_shift = shift_offset / PART_SIZE;
    // Handle the case that the number completely disappears, this resolves nasty two complements handling for negative numbers.
    if (part_shift >= size() || (part_shift + 1 == size() && (m_content[part_shift] >> per_part_shift) == 0)) {
      return operator=(m_positive ? ZERO : MINUS_ONE);
    }
    // Correction for negative numbers because of two complement semantic
    bool extra_bit = false;
    if (!m_positive) {
      // Check if a bit whose whole part gets shifted away is 1
      for (index_type i = 0; i < part_shift && !extra_bit; ++i) {
        extra_bit = m_content[i] != 0;
      }
      // Check if a bit in the part that gets shifted away partially is 1
      extra_bit = extra_bit || (((m_content[part_shift] >> per_part_shift) << per_part_shift) != m_content[part_shift]);
    }
    if (per_part_shift > 0) {
      part_type keep = 0;
      index_type j = size();
      // The strange for loop is necessary because of the unsigned types.
      for (index_type i = 0; i < size(); ++i) {
        --j;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[j] >> per_part_shift) | keep;
        keep = m_content[j] << (PART_SIZE - per_part_shift);
        m_content[j] = shifted;
      }
    }
    if (part_shift > 0) {
      for (ArrayList<part_type>::iterator it = m_content.begin(); it < m_content.end() - part_shift; ++it) {
        *it = it[part_shift];
      }
      for (index_type i = 0; i < part_shift; ++i) {
        m_content.pop();
      }
    }
    if (extra_bit) {
      operator--();
    }
    remove_zeros();
    return *this;
  }

  LongInt& LongInt::pow_eq(index_type exponent)
  {
    ArithmeticHelper::pow_eq(*this, exponent);
    return *this;
  }

  LongInt& LongInt::pow_mod_eq(const LongInt& exponent, const LongInt& modulus)
  {
    ArithmeticHelper::pow_mod_eq(*this, exponent, modulus);
    return *this;
  }

  LongInt& LongInt::operator|=(const LongInt& other)
  {
    bool new_positive = m_positive && other.m_positive;
    bool keep = !m_positive;
    bool other_keep = !other.m_positive;
    bool new_keep = !new_positive;
    for (index_type i = 0; i < std::max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part | other_part, new_keep);
      if (i >= size()) {
        m_content.push(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    assert(keep == 0 && other_keep == 0 && new_keep == 0);
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
    for (index_type i = 0; i < std::max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part ^ other_part, new_keep);
      if (i >= size()) {
        m_content.push(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    assert(keep == 0 && other_keep == 0 && new_keep == 0);
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
    for (index_type i = 0; i < std::max(size(), other.size()); ++i) {
      part_type part, other_part, new_part;
      part = complement_keep(m_positive, part_at(i), keep);
      other_part = complement_keep(other.m_positive, other.part_at(i), other_keep);
      new_part = complement_keep(new_positive, part & other_part, new_keep);
      if (i >= size()) {
        m_content.push(new_part);
      } else {
        m_content[i] = new_part;
      }
    }
    assert(keep == 0 && other_keep == 0 && new_keep == 0);
    m_positive = new_positive;
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
    return *this;
  }

  bool LongInt::is_positive() const
  {
    return m_positive;
  }

  LongInt LongInt::abs() const
  {
    return m_positive ? *this : operator-();
  }

  int inline LongInt::uCompareTo(const LongInt& other) const
  {
    index_type max_index = std::max(size(), other.size());
    for (index_type i = max_index + 1; i > 0;) {
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

  void inline LongInt::remove_zeros()
  {
    while (size() > 1 && m_content[size() - 1] == 0) {
      m_content.pop();
    }
  }

  LongInt::packed_longint_t LongInt::pack() const
  {
    unsigned int* result = new unsigned int[size() * 2];
    for (index_type i = 0; i < size(); ++i) {
      result[2 * i] = (unsigned int)(m_content[i]);
      result[2 * i + 1] = (unsigned int)(m_content[i] >> (PART_SIZE / 2));
    }
    return {result, size() * 2, m_positive};
  }

  LongInt LongInt::mod(const LongInt &modulus) const
  {
    if (modulus < TWO) {
      assert(false);
      throw std::logic_error("Modulus has to be at least 2.");
    }
    LongInt result (operator%(modulus));
    if (!result.m_positive) {
      result += modulus;
    }
    return result;
  }

  LongInt LongInt::mult_inv_mod(const LongInt &modulus) const
  {
    if (modulus < TWO) {
      assert(false);
      throw std::logic_error("Modulus has to be at least 2.");
    }
    return ArithmeticHelper::inv_mod(mod(modulus), modulus);
  }

  LongInt LongInt::add_inv_mod(const LongInt &modulus) const
  {
    if (modulus < TWO) {
      assert(false);
      throw std::logic_error("Modulus has to be at least 2.");
    }
    return operator-().mod(modulus);
  }

  index_type log2(const LongInt& number)
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
        asm("\nincq %0;\n"
        "\tsetc %1;\n"
        : "=q" (part), "=q" (keep) : "0" (part), "1" (keep));
      }
      return part;
    }
  }

  ArrayList<LongInt::part_type>::iterator multiply(const ArrayList<LongInt::part_type>::const_iterator& a_begin,
                                                   const ArrayList<LongInt::part_type>::const_iterator& a_end,
                                                   const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                                                   const ArrayList<LongInt::part_type>::const_iterator& b_end,
                                                   const ArrayList<LongInt::part_type>::iterator& c_begin,
                                                   const ArrayList<LongInt::part_type>::iterator& c_end)
  {
    typedef ArrayList<LongInt::part_type>::const_iterator c_it;
    typedef ArrayList<LongInt::part_type>::iterator it;
    index_type a_size = a_end - a_begin;
    index_type b_size = b_end - b_begin;
    if (a_size <= 0 || b_size <= 0) {
      return c_begin;
    } else if (a_size == 1 && b_size == 1) {
      assert(c_end - c_begin >= 2);
      LongInt::part_type c0, c1;
      asm("mulq %3"
      : "=a" (c0), "=d" (c1) : "a" (*a_begin), "b" (*b_begin));
      it res_begin (c_begin), res_end (c_begin);
      *res_begin = c0;
      ++res_end;
      if (c1 > 0) {
        *res_end = c1;
        ++res_end;
      } else if (*res_begin == 0) {
        return res_begin;
      }
      return res_end;
    }
    index_type max_size = std::max(a_size, b_size);
    index_type part_size = max_size - max_size / 2;
    const c_it& x0_begin (a_begin);
    c_it x0_end (std::min(a_begin + part_size, a_end));
    c_it& x1_begin (x0_end);
    const c_it& x1_end (a_end);
    const c_it& y0_begin (b_begin);
    c_it y0_end (std::min(b_begin + part_size, b_end));
    c_it& y1_begin (y0_end);
    const c_it& y1_end (b_end);
    const it& res_begin (c_begin);

    // z0 = x0 * y0
    const it& z0_begin (res_begin); // Is the first part of the actual result
    it z0_end = multiply(x0_begin, x0_end, y0_begin, y0_end, z0_begin, c_end); // z0 = x0 * y0
    // This has to be padded to size at least 2 * part_size because the final result is constructed here
    for (it z0_it = z0_end; z0_it < z0_begin + 2 * part_size; ++z0_it) {
      *z0_it = 0l;
    }

    // z2 = x1 * y1
    it z2_begin (std::max(z0_end, z0_begin + 2 * part_size)); // Is the second part of the actual result
    it z2_end = multiply(x1_begin, x1_end, y1_begin, y1_end, z2_begin, c_end);
    it res_end (z2_begin + part_size);
    if (z2_begin < z2_end) {
      res_end += part_size;
    }
    assert(z2_end <= res_end); // z2 is part of the result.
    assert(res_end < c_end); // We need enough space for the result
    // This has to be padded to size at least part_size
    for (it z2_it = z2_end; z2_it < res_end; ++z2_it) {
      *z2_it = 0l;
    }
    it z1_begin (res_end);

    // x2 = x0 + x1
    std::pair<c_it, c_it> x2 = calc_xy2(x0_begin, x0_end, x1_begin, x1_end, z1_begin, c_end);
    c_it x2_begin (x2.first), x2_end (x2.second);

    // y2 = y0 + y1
    std::pair<c_it, c_it> y2 = calc_xy2(y0_begin, y0_end, y1_begin, y1_end, z1_begin, c_end);
    c_it y2_begin (y2.first), y2_end (y2.second);

    // z1 = x2 * y2 - z0 - z2
    it z1_end = multiply(x2_begin, x2_end, y2_begin, y2_end, z1_begin, c_end);
    subtract(z1_begin, z1_end, z0_begin, z0_end);
    subtract(z1_begin, z1_end, z2_begin, z2_end);
    while (z1_end > z1_begin && *(z1_end - 1) == 0) {
      --z1_end;
    }

    // Put result together
    add(z0_begin + part_size, res_end, z1_begin, z1_end);
    while (res_end > res_begin && *(res_end - 1) == 0) {
      --res_end;
    }
    return res_end;
  }

  std::pair<ArrayList<LongInt::part_type>::const_iterator, ArrayList<LongInt::part_type>::const_iterator> inline calc_xy2(const ArrayList<LongInt::part_type>::const_iterator& xy0_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy0_end,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy1_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy1_end,
                                                                                                                          ArrayList<LongInt::part_type>::iterator& c_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::iterator& c_end)
  {
    if (xy1_begin < xy1_end) {
      index_type part_size = xy0_end - xy0_begin;
      assert(c_begin + part_size + 1 < c_end); // We need enough space for xy2
      ArrayList<LongInt::part_type>::iterator xy2_begin (c_begin);
      ArrayList<LongInt::part_type>::iterator xy2_end (c_begin + part_size);
      copy(xy2_begin, xy2_end, xy0_begin, xy0_end);
      *(xy2_end++) = 0l;
      add(xy2_begin, xy2_end, xy1_begin, xy1_end);
      // Take out leading zeroes. Is necessary because else size 3 would result in endless recursion.
      while (xy2_end > xy2_begin && *(xy2_end - 1) == 0) {
        --xy2_end;
      }
      c_begin = xy2_end;
      return make_pair(xy2_begin, xy2_end);
    } else {
      return make_pair(xy0_begin, xy0_end);
    }
  }

  void inline add(const ArrayList<LongInt::part_type>::iterator& a_begin,
                  const ArrayList<LongInt::part_type>::iterator& a_end,
                  const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                  const ArrayList<LongInt::part_type>::const_iterator& b_end)
  {
    bool keep = 0;
    ArrayList<LongInt::part_type>::iterator a_it (a_begin);
    ArrayList<LongInt::part_type>::const_iterator b_it (b_begin);
    for (; keep == 1 || b_it < b_end; ++a_it, ++b_it) {
      if (a_it >= a_end)
      assert(a_it < a_end);
      LongInt::part_type b_part = b_it < b_end ? *b_it : 0;
      if (keep) {
        asm("stc;\n"
        "\tadcq %2, %0;\n"
        "\tsetc %1;"
        : "=q" (*a_it), "=q" (keep) : "q" (b_part), "0" (*a_it));
      } else {
        asm("addq %2, %0;\n"
        "\tsetc %1;\n"
        : "=q" (*a_it), "=q" (keep) : "q" (b_part), "0" (*a_it));
      }
    }
  }

  void inline subtract(const ArrayList<LongInt::part_type>::iterator& a_begin,
                       const ArrayList<LongInt::part_type>::iterator& a_end,
                       const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                       const ArrayList<LongInt::part_type>::const_iterator& b_end,
                       bool exchange)
  {
    bool keep = false;
    ArrayList<LongInt::part_type>::iterator a_it (a_begin);
    for (ArrayList<LongInt::part_type>::const_iterator b_it (b_begin); keep == 1 || b_it < b_end; ++a_it, ++b_it) {
      assert(a_it < a_end); // Should never happen because a < b
      LongInt::part_type left = *a_it;
      LongInt::part_type right = b_it < b_end ? *b_it : 0l;
      if (exchange) {
        std::swap(left, right);
      }
      if (keep) {
        asm("stc;\n"
        "\tsbbq %2, %0;\n"
        "\tsetc %1;"
        : "=q" (*a_it), "=q" (keep) : "q" (right), "0" (left));
      } else {
        asm("subq %2, %0;\n"
        "\tsetc %1;\n"
        : "=q" (*a_it), "=q" (keep) : "q" (right), "0" (left));
      }
    }
  }

  static const index_type INITIAL_SPACE_USAGE[][4] = {{0, 0, 0, 0}, {0, 2, 11, 28}, {0, 11, 16, 33}, {0, 28, 33, 42}};

  index_type space_usage(index_type size_a, index_type size_b)
  {
    if (size_a < size_b) {
      return space_usage(size_b, size_a);
    }
    if (size_a < 4) {
      return INITIAL_SPACE_USAGE[size_a][size_b];
    }
    index_type part_size = size_a - size_a / 2;
    if (size_b <= part_size) {
      return space_usage(part_size + 1, size_b) + 4 * part_size + 1;
    } else {
      return space_usage(part_size + 1, part_size + 1) + 6 * part_size + 2;
    }
  }

}
