#include "longint.h"
#include <cmath>
#include <sstream>
#include <cassert>
#include <iostream>

namespace DataStructures {

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
          assert(buffer_size >= s.str().length());
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

  LongInt::LongInt(const LongInt& other):
    m_positive (other.m_positive),
    m_content (other.m_content)
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

  LongInt LongInt::operator~() const
  {
    return --operator-();
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
    return operator+=(one);
  }

  LongInt LongInt::operator--(int)
  {
    LongInt result (*this);
    operator--();
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
    m_content.prepare_size(c_end - c_begin);
    copy(m_content.begin(), m_content.end(), c_begin, c_end);
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
    divide(other, *this, remainder);
    return *this;
  }

  LongInt& LongInt::operator%=(const LongInt& other)
  {
    LongInt quotient;
    divide(other, quotient, *this, true);
    return *this;
  }

  // Note that it is not a problem, if the quotient or remainder is the same as *this because
  // *this gets copied and scaled first.
  void inline LongInt::divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed)
  {
    if (other == zero) {
      throw std::logic_error("Division by zero.");
    }
    // Maximal factor we can multiply the divisor with without increasing its size.
    part_type scale_factor = 1;
    part_type other_last_digit = other.m_content.end()[-1];
    if (other_last_digit + 1 != 0) {
      // (1 << 64) / (other_last_digit + 1)
      asm("movq $0x1, %%rdx;\n"
      "\txorq %%rax, %%rax;\n"
      "\tdiv %1;"
      : "=a" (scale_factor) : "c" (other_last_digit + 1) : "rdx");
    }
    // This scaling does not change the result because it crosses out,
    // but it ensures that the first digit of the divisor is at least 1 << 63.
    LongInt dividend (abs() * scale_factor);
    LongInt divisor (other.abs() * scale_factor);
    part_type divisor_first_digit = divisor.m_content.end()[-1];
    assert(divisor_first_digit >= (1ul << 63));
    index_type divisor_size = divisor.size();
    assert(divisor_size == other.size());
    index_type i = dividend.size();
    // Initialize the results
    quotient = zero;
    remainder = zero;
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
        LongInt back_calculated (divisor * guess);
#ifndef NDEBUG
        index_type old_guess = guess;
#endif
        while (back_calculated > remainder) {
          back_calculated -= divisor;
          --guess;
        }
        assert(back_calculated + divisor > remainder);
        assert(old_guess - guess <= 2);
        remainder -= back_calculated;
        while (quotient.size() <= i) {
          quotient.m_content.push(0);
        }
        quotient.m_content[i] = guess;
      }
    }
    if (remainder_needed) {
      if (scale_factor != 1) {
        // We have to take back the scale_factor
        part_type upper = 0, lower = 0;
        LongInt old_remainder (remainder);
        remainder = zero;
        index_type i = old_remainder.size();
        for (index_type i2 = 0; i2 < old_remainder.size(); ++i2) {
          --i;
          lower = old_remainder.m_content[i];
          while (remainder.size() <= i) {
            remainder.m_content.push(0);
          }
          // upper:lower / scale_factor, store remainder into upper
          asm("div %2;"
          : "=a" (remainder.m_content[i]), "=d" (upper) : "q" (scale_factor), "a" (lower), "d" (upper));
        }
        // The division has to work without remainder
        assert(upper == 0);
      }
      remainder.m_positive = m_positive;
    }
    quotient.m_positive = m_positive == other.m_positive;
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
      return operator=(m_positive ? zero : minus_one);
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
    LongInt result (one);
    unsigned int j = sizeof(index_type) * CHAR_BIT;
    for (unsigned int j2 = 0; j2 < sizeof(index_type) * CHAR_BIT; ++j2) {
      --j;
      if ((exponent >> j) & 1) {
        result *= *this;
      }
      if (j > 0) {
        result *= result;
      }
    }
    return operator=(result);
  }

  LongInt& LongInt::pow_mod_eq(const LongInt& exponent, const LongInt& modulus)
  {
    assert(exponent >= 0);
    LongInt result (one);
    unsigned int j = sizeof(index_type) * CHAR_BIT;
    for (unsigned int j2 = 0; j2 < sizeof(index_type) * CHAR_BIT; ++j2) {
      --j;
      if (((exponent >> j) & 1) == 1) {
        result *= *this;
      }
      if (j > 0) {
        result *= result;
      }
      result %= modulus;
    }
    return operator=(result);
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
    index_type i = max_index;
    for (index_type j = 0; j < max_index; j++) {
      i--;
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

  LongInt::part_type inline LongInt::part_at(index_type i) const
  {
    return i < size() ? m_content[i] : 0l;
  }

  LongInt LongInt::inv_mod(const LongInt &modulus) const
  {
    LongInt a = modulus.abs();
    if (a <= 1) {
      throw std::logic_error("Modulo 0 and 1, there are no multiplicative inverses.");
    }
    LongInt b = abs();
    LongInt u_old = 0;
    LongInt u = 1;
    LongInt v_old = 1;
    LongInt v = 0;
    if (b >= a) {
      b %= a;
    }
    while (b > 0) {
      LongInt q;
      a.divide(b, q, a, true);
      u_old -= u * q;
      v_old -= v * q;
      std::swap(a, b);
      std::swap(u, u_old);
      std::swap(v, v_old);
    }
    if (a != 1) {
      std::ostringstream oss;
      oss << "*this (" << *this << ") and modulus (" << modulus << ") are not relatively prime, the gcd is " << a << ", hence no multiplicative inverse exists.";
      throw std::logic_error(oss.str());
    }
    u_old += modulus;
    u_old %= modulus;
    return u_old;
  }

  LongInt gcd(const LongInt &first, const LongInt &second)
  {
    LongInt a = first.abs();
    LongInt b = second.abs();
    if (first < second) {
      std::swap(a, b);
    }
    while (b > 0) {
      a %= b;
      std::swap(a, b);
    }
    return a;
  }

  index_type log2(const LongInt& number)
  {
    return (number.size() - 1) * LongInt::PART_SIZE + log2(number.m_content[number.size() - 1]);
  }

  LongInt rand_bits(index_type number_bits)
  {
    static const index_type RAND_BITS = log2((index_type) RAND_MAX + 1);
    // static_assert((1 << RAND_BITS) == RAND_MAX + 1);
    LongInt result (0);
    while (number_bits >= RAND_BITS) {
      result <<= RAND_BITS;
      result += rand();
      number_bits -= RAND_BITS;
    }
    result += rand() % (1 << number_bits);
    return result;
  }

  LongInt rand_number(const LongInt& max_number)
  {
    LongInt result;
    index_type bits = log2(max_number);
    do {
      result = rand_bits(bits);
    } while (result >= max_number);
    return result;
  }

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, bool& keep)
  {
    if (positive) {
      return part;
    } else {
      part = ~part;
      if (keep) {
        asm("incq %0;\n"
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
