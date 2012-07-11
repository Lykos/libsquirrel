#include "longint.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <cassert>

namespace DataStructures {

  static const int UNSIGNED_LONG_BITS = sizeof(LongInt::part_type) * CHAR_BIT;
  static const int LOWER_BITS = UNSIGNED_LONG_BITS / 2;
  static const LongInt::part_type LOWER_MASK = (1l << (UNSIGNED_LONG_BITS / 2)) - 1;

  static const LongInt minus_one (-1);
  static const LongInt zero (0);
  static const LongInt one (1);
  static const LongInt two (2);
  static const LongInt three (3);
  static const LongInt four (4);
  static const LongInt five (5);
  static const LongInt six (6);
  static const LongInt seven (7);
  static const LongInt eight (8);
  static const LongInt nine (9);
  static const LongInt ten (10);

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
      ArrayList<std::string> digits;
      std::ostringstream s;
      i.m_positive = true;
      while (i > 0) {
        digits.push((i % base).to_digit());
        i /= base;
      }
      if (digits.is_empty()) {
        return out << "0";
      }
      while (!digits.is_empty()) {
        s << digits.pop();
      }
      return out << s.str();
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
    m_content.push(0);
    std::string::const_iterator it = numerical_string.begin();
    if (*it == '-') {
      positive = false;
      it++;
    } else if (numerical_string[0] == '+') {
      it++;
    }
    for (; it < numerical_string.end(); it++) {
      operator*=(ten);
      if (*it == '9') {
        operator+=(nine);
      } else if (*it == '8') {
        operator+=(eight);
      } else if (*it == '7') {
        operator+=(seven);
      } else if (*it == '6') {
        operator+=(six);
      } else if (*it == '5') {
        operator+=(five);
      } else if (*it == '4') {
        operator+=(four);
      } else if (*it == '3') {
        operator+=(three);
      } else if (*it == '2') {
        operator+=(two);
      } else if (*it == '1') {
        operator+=(one);
      } else if (*it != '0') {
        throw std::logic_error("Non digit in numerical string.");
      }
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
    result += other;
    return result;
  }

  LongInt LongInt::operator-(const LongInt& other) const
  {
    LongInt result(*this);
    result -= other;
    return result;
  }

  LongInt LongInt::operator*(const LongInt& other) const
  {
    LongInt result(*this);
    result *= other;
    return result;
  }

  LongInt LongInt::operator<<(index_type shift_offset) const
  {
    LongInt result(*this);
    result <<= shift_offset;
    return result;
  }

  LongInt LongInt::operator>>(index_type shift_offset) const
  {
    LongInt result(*this);
    result >>= shift_offset;
    return result;
  }

  LongInt LongInt::operator%(const LongInt& other) const
  {
    LongInt result(*this);
    result %= other;
    return result;
  }

  LongInt LongInt::operator/(int other) const
  {
    LongInt result(*this);
    result /= other;
    return result;
  }

  LongInt LongInt::operator++(int)
  {
    LongInt result (*this);
    operator+=(one);
    return result;
  }

  LongInt& LongInt::operator++()
  {
    operator+=(one);
    return *this;
  }

  LongInt LongInt::operator--(int)
  {
    LongInt result (*this);
    operator-=(one);
    return result;
  }

  LongInt& LongInt::operator--()
  {
    operator-=(one);
    return *this;
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
    if (operator==(zero)) {
      return *this;
    } else if (other == zero) {
      return operator=(LongInt(0));
    } else if (other.size() == 1 && size() == 1) {
      part_type product = m_content[0] * other.m_content[0];
      m_content[0] = lower_half(product);
      part_type upper = upper_half(product);
      if (upper > 0) {
        m_content.push(upper);
      }
      m_positive = m_positive == other.m_positive;
      return *this;
    }
    bool positive = m_positive;
    m_positive = true;
    index_type max_size = std::max(size(), other.size());
    index_type part_size = next_higher(max_size) / 2;
    LongInt x0 (lower_part(part_size));
    LongInt x1 (upper_part(part_size));
    LongInt y0 (other.lower_part(part_size));
    LongInt y1 (other.upper_part(part_size));
    LongInt z2 (x1 * y1);
    LongInt z0 (x0 * y0);
    LongInt z1 ((x1 + x0) * (y1 + y0) - z2 - z0);
    m_content = z2.m_content;
    operator<<=(part_size * PART_SIZE);
    operator+=(z1);
    operator<<=(part_size * PART_SIZE);
    operator+=(z0);
    m_positive = positive == other.m_positive;
    remove_zeros();
    return *this;
  }


  LongInt& LongInt::operator<<=(index_type shift_offset)
  {
    index_type per_part_shift = shift_offset % PART_SIZE;
    index_type part_shift = shift_offset / PART_SIZE;
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
    if (part_shift > 0) {
      m_content = ArrayList<part_type> (part_shift, 0) + m_content;
    }
    return *this;
  }

  LongInt& LongInt::operator>>=(index_type shift_offset)
  {
    index_type per_part_shift = shift_offset % PART_SIZE;
    index_type part_shift = shift_offset / PART_SIZE;
    if (part_shift >= size()) {
      operator=(m_positive ? zero : minus_one);
    } else {
      bool extra_bit = ((m_content[part_shift] >> per_part_shift) & 1) && !m_positive;
      part_type keep = 0;
      index_type j = m_content.size();
      // The strange for loop is because of the unsigned types.
      for (index_type i = 0; i < m_content.size(); ++i) {
        --j;
        // Or works because exactly the space needed for keep gets shifted away.
        part_type shifted = (m_content[i] << (PART_SIZE - per_part_shift)) | keep;
        m_content[i] = upper_half(shifted);
        keep = lower_half(shifted);
      }
      if (part_shift > 0) {
        m_content = ArrayList<part_type> (m_content.begin() + part_shift, m_content.end());
      }
      // Adding one bit could be made slightly more efficient
      if (extra_bit) {
        operator+=(one);
      }
    }
    return *this;
  }

  LongInt& LongInt::operator%=(const LongInt& other)
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
    m_positive = m_positive == other.m_positive;
    return operator=(result);
  }

  LongInt& LongInt::operator/=(const LongInt& other)
  {
    if (other == zero) {
      throw std::logic_error("Division by zero.");
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
        if (active_part > divisor) {
          result += two_power;
          active_part -= divisor;
        }
      }
    }
    m_positive = m_positive == other.m_positive;
    return operator=(result);
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

  std::string LongInt::to_digit() const
  {
    std::stringstream s;
    s << m_content[0];
    // TODO The thing with size is not actually correct, but works for the cases where we use it.
    if (size() > 1 || m_content[0] > 9 || !m_positive) {
      throw std::logic_error("Something that is not a digit has been converted to one.");
    }
    return s.str();
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
