#include "longint.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <cassert>

namespace DataStructures {

  static const int UNSIGNED_LONG_BITS = sizeof(LongInt::part_type) * CHAR_BIT;
  static const int LOWER_BITS = UNSIGNED_LONG_BITS / 2;
  static const LongInt::part_type LOWER_MASK = (1l << (UNSIGNED_LONG_BITS / 2)) - 1;
  static const unsigned int buffer_size = (LongInt::PART_SIZE * 1233) >> 12;

  static const LongInt minus_one (-1);
  static const LongInt zero (0);
  static const LongInt one (1);
  static const LongInt ten (10);
  static const LongInt buffer_factor (ten.pow(buffer_size));

  static const index_type base (10);

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt)
  {
    if (!longInt.m_positive) {
      out << "-";
    }
    LongInt i (longInt.abs());
    if (i.size() == 1) {
      return out << longInt.m_content[0];
    } else {
      ArrayList<std::string> parts;
      i.m_positive = true;
      while (i > 0) {
        std::ostringstream s;
        s << (i % buffer_factor).m_content[0];
        parts.push(s.str());
        i /= buffer_factor;
        if (i > 0) {
          for (unsigned int j = 0; j < buffer_size - s.str().length(); ++j) {
            parts.push("0");
          }
        }
      }
      if (parts.is_empty()) {
        return out << "0";
      }
      while (!parts.is_empty()) {
        out << parts.pop();
      }
      return out;
    }
  }

  std::istream& operator>>(std::istream& in, LongInt& longInt)
  {
    std::string s;
    std::istream& res = in >> s;
    longInt = LongInt(s);
    return res;
  }

  LongInt::LongInt(long long int initial): m_positive(initial >= 0)
  {
    part_type positive_part = m_positive ? initial : -initial;
    part_type lower = lower_half(positive_part);
    part_type upper = upper_half(positive_part);
    m_content.push(lower);
    if (upper > 0) {
      m_content.push(upper);
    }
  }

  LongInt::LongInt(const LongInt& other): m_positive(other.m_positive), m_content(other.m_content)
  {
  }

  LongInt::LongInt(const std::string& numerical_string)
  {
    m_positive = true;
    bool positive = true;
    unsigned int start_index = 0;
    m_content.push(0);
    std::string::const_iterator it = numerical_string.begin();
    if (*it == '-') {
      positive = false;
      ++it;
      ++start_index;
    } else if (*it == '+') {
      ++it;
      ++start_index;
    }
    for (; it < numerical_string.end(); ++it) {
      if (*it > '9' || *it < '0') {
        throw std::logic_error("Non digit in numerical string.");
      }
    }
    unsigned int i;
    for (i = start_index; i + buffer_size < numerical_string.length(); i += buffer_size) {
      operator*=(buffer_factor);
      std::istringstream is (numerical_string.substr(i, buffer_size));
      part_type part;
      is >> part;
      operator+=(part);
    }
    unsigned int rest_length = numerical_string.length() - i;
    if (rest_length > 0) {
      LongInt ten_pow (ten);
      ten_pow.pow_eq(rest_length);
      operator*=(ten_pow);
      std::istringstream is (numerical_string.substr(i, buffer_size));
      part_type part;
      is >> part;
      operator+=(part);
    }
    m_positive = positive;
  }

  LongInt LongInt::operator-() const
  {
    if (operator==(zero)) {
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

    if (operator==(zero) || other == zero) {
      return zero;
    } else if (other.size() == 1 && size() == 1) {
      part_type product = m_content[0] * other.m_content[0];
      LongInt result;
      result.m_content[0] = lower_half(product);
      part_type upper = upper_half(product);
      if (upper > 0) {
        result.m_content.push(upper);
      }
      result.m_positive = m_positive == other.m_positive;
      return result;
    }
    index_type max_size = std::max(size(), other.size());
    index_type part_size = next_higher(max_size) / 2;
    LongInt x0 (lower_part(part_size));
    LongInt x1 (upper_part(part_size));
    LongInt y0 (other.lower_part(part_size));
    LongInt y1 (other.upper_part(part_size));
    LongInt z2 (zero);
    if (size() > part_size && other.size() > part_size) {
      z2 = x1 * y1;
    }
    LongInt z0 (x0 * y0);
    x1 += x0;
    y1 += y0;
    LongInt z1 (x1 * y1);
    z1 -= z0;
    z1 -= z2;
    z2 <<= part_size * PART_SIZE;
    z2 += z1;
    z2 <<= part_size * PART_SIZE;
    z2 += z0;
    z2.m_positive = m_positive == other.m_positive;
    z2.remove_zeros();
    return z2;
  }

  LongInt LongInt::operator/(const LongInt& other) const
  {
    if (other == zero) {
      throw std::logic_error("Division by zero.");
    }
    // This is necessary because the zero would mess up the rounding towards negative infinity.
    if (*this == zero) {
      return *this;
    }
    LongInt divisor (other.abs());
    LongInt result (zero);
    LongInt two_power (one);
    LongInt active_part (zero);
    two_power <<= size() * PART_SIZE;
    index_type i = size();
    // Strange for loop necessary because of unsigned types.
    for (index_type i2 = 0; i2 < size(); ++i2) {
      --i;
      index_type j = PART_SIZE;
      for (unsigned int j2 = 0; j2 < PART_SIZE; ++j2) {
        j--;
        two_power >>= 1;
        active_part <<= 1;
        if ((m_content[i] >> j) & 1) {
          active_part += 1;
        }
        if (active_part >= divisor) {
          result += two_power;
          active_part -= divisor;
        }
      }
    }
    result.m_positive = m_positive == other.m_positive;
    // Round to negative infinity hack
    if (!result.m_positive && active_part != zero) {
      result -= one;
    }
    return result;
  }

  LongInt LongInt::operator%(const LongInt& other) const
  {
    if (other == zero) {
      throw std::logic_error("Division by zero.");
    }
    LongInt result (zero);
    LongInt two_power (one);
    if (!other.m_positive) {
      two_power += other;
    }
    for (index_type i = 0; i < size(); ++i) {
      for (unsigned int j = 0; j < PART_SIZE; ++j) {
        if ((m_content[i] >> j) & 1) {
          if (m_positive) {
            result += two_power;
            if (other.m_positive && result >= other) {
              result -= other;
            } else if (!other.m_positive && result <= other) {
              result -= other;
            }
          } else {
            result -= two_power;
            if (other.m_positive && result < 0) {
              result += other;
            } else if (!other.m_positive && result > 0) {
              result += other;
            }
          }
        }
        two_power <<= 1;
        if (other.m_positive && two_power >= other) {
          two_power -= other;
        } else if (!other.m_positive && two_power <= other) {
          two_power -= other;
        }
      }
    }
    return result;
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

  LongInt LongInt::pow(index_type other) const
  {
    LongInt result(*this);
    return result.pow_eq(other);
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
    operator+=(one);
    return result;
  }

  LongInt& LongInt::operator++()
  {
    return operator+=(one);
  }

  LongInt LongInt::operator--(int)
  {
    LongInt result (*this);
    operator-=(one);
    return result;
  }

  LongInt& LongInt::operator--()
  {
    return operator-=(one);
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

  bool LongInt::operator<(const LongInt& other) const
  {
    return compareTo(other) == -1;
  }

  bool LongInt::operator<=(const LongInt& other) const
  {
    int res = compareTo(other);
    return res == -1 || res == 0;
  }

  bool LongInt::operator==(const LongInt& other) const
  {
    return compareTo(other) == 0;
  }

  bool LongInt::operator>=(const LongInt& other) const
  {
    int res = compareTo(other);
    return res == 1 || res == 0;
  }

  bool LongInt::operator>(const LongInt& other) const
  {
    return compareTo(other) == 1;
  }

  bool LongInt::operator!=(const LongInt& other) const
  {
    return compareTo(other) != 0;
  }

  LongInt& LongInt::operator=(const LongInt& other)
  {
    if (&other == this) {
      return *this;
    }
    m_positive = other.m_positive;
    m_content = other.m_content;
    return *this;
  }

  LongInt& LongInt::operator+=(const LongInt& other)
  {
    if (other == zero) {
      return *this;
    }
    if (other.m_positive != m_positive) {
      return operator-=(-other);
    }
    part_type keep = 0;
    index_type i = 0;
    while (keep != 0 || i < other.m_content.size()) {
      if (i >= m_content.size()) {
        m_content.push(0);
      }
      part_type sum = m_content[i] + keep;
      if (i < other.m_content.size()) {
        sum += other.m_content[i];
      }
      m_content[i] = lower_half(sum);
      keep = upper_half(sum);
      i++;
    }
    return *this;
  }

  static const LongInt::part_type MAX_PART = (1l << LongInt::PART_SIZE) - 1;

  LongInt& LongInt::operator-=(const LongInt& other)
  {
    if (other == zero) {
      return *this;
    }
    if (other.m_positive != m_positive) {
      return operator+=(-other);
    }
    if ((m_positive && *this < other) || (!m_positive && *this > other)) {
      return operator=(-(other - *this));
    }
    bool keep = false;
    index_type i = 0;
    while (keep || i < other.m_content.size()) {
      if (i >= m_content.size()) {
        // can only happen if the rest of the other numbers content is 0 because the other number is at most this number.
        break;
      }
      part_type left = m_content[i];
      part_type right = (i < other.m_content.size()) ? other.m_content[i] : 0;
      if (keep) {
        if (left <= right) {
          // leave keep true
          left += MAX_PART;
        } else {
          --left;
          keep = false;
        }
      } else if (left < right) {
        left += MAX_PART + 1;
        keep = true;
      }
      m_content[i++] = left - right;
    }
    remove_zeros();
    if (size() == 1 && m_content[0] == 0) {
      m_positive = true;
    }
    return *this;
  }

  LongInt& LongInt::operator*=(const LongInt& other)
  {
    return operator=(operator*(other));
  }

  LongInt& LongInt::operator/=(const LongInt& other)
  {
    return operator=(operator/(other));
  }

  LongInt& LongInt::operator%=(const LongInt& other)
  {
    return operator=(operator%(other));
  }

  LongInt& LongInt::operator<<=(index_type shift_offset)
  {
    index_type per_part_shift = shift_offset % PART_SIZE;
    index_type part_shift = shift_offset / PART_SIZE;
    if (per_part_shift != 0) {
      part_type keep = 0;
      for (index_type i = 0; keep != 0 || i < m_content.size(); ++i) {
        if (i >= m_content.size()) {
          m_content.push(0);
        }
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[i] << per_part_shift) | keep;
        m_content[i] = lower_half(shifted);
        keep = upper_half(shifted);
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
    if (part_shift >= size() || (part_shift + 1 == size() && (1u << per_part_shift) > m_content[part_shift])) {
      return operator=(m_positive ? zero : minus_one);
    }
    // Correction for negative numbers because of two complement semantic
    bool extra_bit = false;
    if (!m_positive) {
      for (index_type i = 0; i < part_shift && !extra_bit; ++i) {
        extra_bit = m_content[i] != 0;
      }
      extra_bit = extra_bit || (m_content[part_shift] & ((1 << per_part_shift) - 1)) != 0;
    }
    if (per_part_shift > 0) {
      part_type keep = 0;
      index_type j = m_content.size();
      // The strange for loop is necessary because of the unsigned types.
      for (index_type i = 0; i < m_content.size(); ++i) {
        --j;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[j] << (PART_SIZE - per_part_shift)) | (keep << PART_SIZE);
        m_content[j] = upper_half(shifted);
        keep = lower_half(shifted);
      }
    }
    if (part_shift > 0) {
      m_content = ArrayList<part_type> (m_content.begin() + part_shift, m_content.end());
    }
    // Adding one bit could be made slightly more efficient
    if (extra_bit) {
      operator--();
    }
    remove_zeros();
    return *this;
  }

  LongInt& LongInt::pow_eq(index_type other)
  {
    LongInt result (one);
    unsigned int j = sizeof(index_type) * CHAR_BIT;
    for (unsigned int j2 = 0; j2 < sizeof(index_type) * CHAR_BIT; ++j2) {
      --j;
      if ((other >> j) & 1) {
        result *= *this;
      }
      if (j > 0) {
        result *= result;
      }
    }
    return operator=(result);
  }

  LongInt& LongInt::operator|=(const LongInt& other)
  {
    return *this;
  }

  LongInt& LongInt::operator^=(const LongInt& other)
  {
    return *this;
  }

  LongInt& LongInt::operator&=(const LongInt& other)
  {
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

  LongInt::LongInt(const ArrayList<part_type>& content): m_positive(true), m_content(content)
  {
    if (m_content.is_empty()) {
      m_content.push(0);
    }
  }

  index_type inline LongInt::size() const
  {
    return m_content.size();
  }

  LongInt LongInt::lower_part(index_type part_size) const
  {
    ArrayList<part_type> part (m_content.begin(), std::min(m_content.end(), m_content.begin() + part_size));
    return LongInt(part);
  }

  LongInt LongInt::upper_part(index_type part_size) const
  {
    ArrayList<part_type> part (m_content.begin() + part_size, std::max(m_content.end(), m_content.begin() + part_size));
    return LongInt(part);
  }

  int LongInt::uCompareTo(const LongInt& other) const
  {
    index_type max_index = std::max(size(), other.size());
    index_type i = max_index;
    for (index_type j = 0; j < max_index; j++) {
      i--;
      part_type my = 0;
      part_type his = 0;
      if (size() > i) {
        my = m_content[i];
      }
      if (other.size() > i) {
        his = other.m_content[i];
      }
      if (my > his) {
        return 1;
      } else if (his > my) {
        return -1;
      }
      if (i == 0) {
        // Because of the unsignedness, the while condition doesn't really work.
        return 0;
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

  LongInt::part_type upper_half(LongInt::part_type i)
  {
    return i >> LOWER_BITS;
  }

  LongInt::part_type lower_half(LongInt::part_type i)
  {
    return i & LOWER_MASK;
  }

}
