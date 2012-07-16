#include "longint.h"
#include <cmath>
#include <sstream>
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
    index_type part_size = max_size - max_size / 2;
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

  void inline LongInt::pad_zeros(index_type new_size)
  {
    assert(new_size >= size());
    ArrayList<part_type>::iterator old_end = m_content.end();
    m_content.prepare_size(new_size);
    for (; old_end < m_content.end(); ++old_end) {
      *old_end = 0l;
    }
  }

  static const LongInt::part_type MAX_PART = (1l << LongInt::PART_SIZE) - 1;

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
      for (index_type i = 0; keep != 0 || i < size(); ++i) {
        if (i >= size()) {
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
      index_type j = size();
      // The strange for loop is necessary because of the unsigned types.
      for (index_type i = 0; i < size(); ++i) {
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
    bool new_positive = m_positive && other.m_positive;
    part_type keep = !m_positive;
    part_type other_keep = !other.m_positive;
    part_type new_keep = !new_positive;
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
    return *this;
  }

  LongInt& LongInt::operator^=(const LongInt& other)
  {
    bool new_positive = other.m_positive ^ other.m_positive;
    part_type keep = !m_positive;
    part_type other_keep = !other.m_positive;
    part_type new_keep = !new_positive;
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
    return *this;
  }

  LongInt& LongInt::operator&=(const LongInt& other)
  {
    bool new_positive = other.m_positive || other.m_positive;
    part_type keep = !m_positive;
    part_type other_keep = !other.m_positive;
    part_type new_keep = !new_positive;
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

  LongInt::part_type inline LongInt::part_at(index_type i) const
  {
    return i < size() ? m_content[i] : 0l;
  }

  LongInt::part_type inline upper_half(LongInt::part_type part)
  {
    return part >> LOWER_BITS;
  }

  LongInt::part_type inline lower_half(LongInt::part_type part)
  {
    return part & LOWER_MASK;
  }

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, LongInt::part_type& keep)
  {
    if (positive) {
      return part;
    } else {
      assert(keep == 0 || keep == 1);
      LongInt::part_type tmp = ~part + keep;
      keep = ~upper_half(tmp) & 1;
      return lower_half(tmp);
    }
  }

  ArrayList<LongInt::part_type>::iterator multiply(ArrayList<LongInt::part_type>::const_iterator a_begin,
                                                   ArrayList<LongInt::part_type>::const_iterator a_end,
                                                   ArrayList<LongInt::part_type>::const_iterator b_begin,
                                                   ArrayList<LongInt::part_type>::const_iterator b_end,
                                                   ArrayList<LongInt::part_type>::iterator c_begin,
                                                   ArrayList<LongInt::part_type>::iterator c_end)
  {
    typedef ArrayList<LongInt::part_type>::const_iterator c_it;
    typedef ArrayList<LongInt::part_type>::iterator it;
    if (a_begin <= a_end || b_begin <= b_end) {
      return c_begin;
    } else if (a_begin + 1 == a_end && b_begin + 1 == b_end) {
      assert(c_end - c_begin >= 2);
      LongInt::part_type c = *a_begin * *b_begin;
      *c_begin = lower_half(c);
      LongInt::part_type upper = upper_half(c);
      if (upper > 0) {
        *(++c_begin) = upper;
      }
      return ++c_begin;
    }
    index_type a_size = a_end - a_begin;
    index_type b_size = b_end - b_begin;
    index_type max_size = std::max(a_size, b_size);
    index_type part_size = max_size - max_size / 2;
    c_it x0_begin (a_begin);
    c_it x0_end (std::min(a_begin + part_size, a_end));
    c_it x1_begin (x0_end);
    c_it x1_end (a_end);
    c_it y0_begin (b_begin);
    c_it y0_end (std::min(b_begin + part_size, b_end));
    c_it y1_begin (y0_end);
    c_it y1_end (b_end);
    it z0_begin (c_begin); // Is the first part of the actual result
    it z0_end = multiply(x0_begin, x0_end, y0_begin, y0_end, z0_begin, c_end); // z0 = x0 * y0
    it z2_begin (c_begin + 2 * part_size); // Is the second part of the actual result
    it z2_end = multiply(x1_begin, x1_end, y1_begin, y1_end, z2_begin, c_end); // z2 = x1 * y1
    it z1_begin (c_begin + 4 * part_size);
    // x2 = x0 + x1
    c_it x2_begin (x0_begin), x2_end (x0_end);
    if (x1_begin < x1_end) {
      it tmp_x2_begin (z1_begin);
      it tmp_x2_end (z1_begin);
      copy(tmp_x2_begin, tmp_x2_end, x0_begin, x0_end);
      add(tmp_x2_begin, tmp_x2_end, x1_begin, x1_end);
      x2_begin = tmp_x2_begin;
      x2_end = tmp_x2_end;
      z1_begin = tmp_x2_end;
    }
    // y2 = y0 + y1
    c_it y2_begin (y0_begin), y2_end (y0_end);
    if (y1_begin < y1_end) {
      it tmp_y2_begin (z1_begin);
      it tmp_y2_end (z1_begin + part_size);
      copy(tmp_y2_begin, tmp_y2_end, y0_begin, y0_end);
      add(tmp_y2_begin, tmp_y2_end, y1_begin, y1_end);
      y2_begin = tmp_y2_begin;
      y2_end = tmp_y2_end;
      z1_begin = tmp_y2_end;
    }
    it z1_end = multiply(x2_begin, x2_end, y2_begin, y2_end, z1_begin, c_end);
    subtract(z1_begin, z1_end, z0_begin, z0_end);
    subtract(z1_begin, z1_end, z2_begin, z2_end);
    add(c_begin + part_size, c_begin + part_size * 4, z1_begin, z1_end);
    return c_begin + part_size * 4;
  }

  void inline add(ArrayList<LongInt::part_type>::iterator a_begin,
           ArrayList<LongInt::part_type>::iterator a_end,
           ArrayList<LongInt::part_type>::const_iterator b_begin,
           ArrayList<LongInt::part_type>::const_iterator b_end)
  {
    LongInt::part_type keep = 0l;
    for (; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
      assert(keep == 0 || keep == 1);
      assert(a_begin < a_end);
      LongInt::part_type sum = *a_begin + keep;
      if (b_begin < b_end) {
        sum += *b_begin;
      }
      *a_begin = lower_half(sum);
      keep = upper_half(sum);
    }
  }

  void inline subtract(ArrayList<LongInt::part_type>::iterator a_begin,
                ArrayList<LongInt::part_type>::iterator a_end,
                ArrayList<LongInt::part_type>::const_iterator b_begin,
                ArrayList<LongInt::part_type>::const_iterator b_end,
                bool exchange)
  {
    LongInt::part_type keep = 0l;
    for (; keep == 1 || b_begin < b_end; ++a_begin, ++b_begin) {
      assert(keep == 0 || keep == 1);
      assert(a_begin < a_end); // Should never happen because a < b
      LongInt::part_type left = *a_begin;
      LongInt::part_type right = b_begin < b_end ? *b_begin : 0l;
      if (exchange) {
        std::swap(left, right);
      }
      if (keep == 1) {
        if (left <= right) {
          // leave keep true
          left += MAX_PART;
        } else {
          --left;
          keep = 0l;
        }
      } else if (left < right) {
        left += MAX_PART + 1;
        keep = 1l;
      }
      *a_begin = left - right;
    }
  }

  index_type inline space_usage(index_type size_a, index_type size_b)
  {
    part_size = size_a - size_a / 2;
  }

}
