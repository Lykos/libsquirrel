#include "longint.h"
#include "algebrahelper.h"
#include "multiply.h"
#include "divide.h"
#include "add.h"
#include "subtract.h"
#include <cmath>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <string>
#include <climits>

namespace DataStructures {

  using namespace ArithmeticHelper;
  using namespace LongArithmetic;

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

  static const uint_fast8_t base (10);

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
    LongInt::size_type length = s.length();
    LongInt::size_type start_index = longInt.read_sign(s);
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

  LongInt::LongInt(const std::string& numerical_string)
  {
    if (numerical_string.empty()) {
      throw std::logic_error("Empty numerical string is not allowed.");
    }
    size_type length = numerical_string.length();
    size_type start_index = read_sign(numerical_string);
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

  inline LongInt::size_type LongInt::read_sign(const std::string& numerical_string)
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

  inline void LongInt::read_decimal(const std::string& numerical_string, size_type start_index)
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

  inline void LongInt::read_hexadecimal(const std::string& numerical_string, size_type start_index)
  {
    if (start_index == numerical_string.length()) {
      throw std::logic_error("Numerical string without digits is not allowed.");
    }
    for (std::string::const_iterator it = numerical_string.begin() + start_index; it < numerical_string.end(); ++it) {
      if ((*it > '9' || *it < '0') && (*it > 'F' || *it < 'A') && (*it > 'f' || *it < 'a')) {
        throw std::logic_error("Non digit in numerical string.");
      }
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
      std::istringstream iss (numerical_string.substr(i, HEXADECIMAL_BUFFER_SIZE));
      iss >> std::hex >> m_content[j];
      ++j;
    }
    std::istringstream iss (numerical_string.substr(start_index, i - start_index));
    iss >> std::hex >> m_content[j];
  }

  inline void LongInt::read_octal(const std::string& numerical_string, size_type start_index)
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

  inline void LongInt::write_octal(std::ostream& out) const
  {
    throw std::logic_error("Octal is not implemented yet.");
  }

  inline void LongInt::write_hexadecimal(std::ostream& out) const
  {
    for (size_type i = m_content.size(); i > 0;) {
      --i;
      std::ostringstream oss;
      oss.flags(std::ios_base::hex);
      oss << m_content[i];
      for (uint_fast16_t j = oss.str().size(); j < sizeof(part_type) * 2; ++j) {
        out << '0';
      }
      out << oss.str();
      oss.flush();
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

  LongInt LongInt::operator<<(size_type shift_offset) const
  {
    LongInt result(*this);
    return result <<= shift_offset;
  }

  LongInt LongInt::operator>>(size_type shift_offset) const
  {
    LongInt result(*this);
    return result >>= shift_offset;
  }

  LongInt LongInt::pow(size_type exponent) const
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
    DataStructures::add(&m_content[0],
                        &m_content[0] + size(),
                        &other.m_content[0],
                        &other.m_content[0] + other.size());
    remove_zeros();
  }

  inline void LongInt::pad_zeros(size_type new_size)
  {
    for (size_type i = size(); i < new_size; ++i) {
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
    m_content.push_all(c, c_end);
    free(c);
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

  LongInt& LongInt::operator<<=(size_type shift_offset)
  {
    size_type per_part_shift = shift_offset % PART_SIZE;
    size_type part_shift = shift_offset / PART_SIZE;
    if (per_part_shift != 0) {
      part_type keep = 0;
      for (size_type i = 0; keep != 0 || i < size(); ++i) {
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
      m_content = part_list (part_shift, 0) + m_content;
    }
    return *this;
  }

  LongInt& LongInt::operator>>=(size_type shift_offset)
  {
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
        m_content.pop();
      }
    }
    if (extra_bit) {
      operator--();
    }
    remove_zeros();
    return *this;
  }

  LongInt& LongInt::pow_eq(size_type exponent)
  {
    AlgebraHelper::pow_eq(*this, exponent);
    return *this;
  }

  LongInt& LongInt::pow_mod_eq(const LongInt& exponent, const LongInt& modulus)
  {
    AlgebraHelper::pow_mod_eq(*this, exponent, modulus);
    return *this;
  }

  LongInt& LongInt::operator|=(const LongInt& other)
  {
    bool new_positive = m_positive && other.m_positive;
    bool keep = !m_positive;
    bool other_keep = !other.m_positive;
    bool new_keep = !new_positive;
    for (size_type i = 0; i < std::max(size(), other.size()); ++i) {
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
    for (size_type i = 0; i < std::max(size(), other.size()); ++i) {
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
    for (size_type i = 0; i < std::max(size(), other.size()); ++i) {
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
    size_type max_index = std::max(size(), other.size());
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
      m_content.pop();
    }
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
    return AlgebraHelper::inv_mod(mod(modulus), modulus);
  }

  LongInt LongInt::add_inv_mod(const LongInt &modulus) const
  {
    if (modulus < TWO) {
      assert(false);
      throw std::logic_error("Modulus has to be at least 2.");
    }
    return operator-().mod(modulus);
  }

  LongInt::exponent_type log2(const LongInt& number)
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

}
