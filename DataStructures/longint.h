#ifndef DATASTRUCTURES_LONGINT_H
#define DATASTRUCTURES_LONGINT_H

#include "arraylist.h"
#include <cstdint>
#include <istream>
#include <ostream>

namespace DataStructures {

  class LongInt;

  class LongIntConverter;

  class UniformLongIntDistribution;

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

  std::istream& operator>>(std::istream& in, LongInt& longInt);

  class LongInt
  {
    friend std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

    friend std::istream& operator>>(std::istream& in, LongInt& longInt);

    friend ArrayList<uint64_t>::size_type log2(const LongInt& number);

    friend class UniformLongIntDistribution;

    friend class LongIntConverter;

  public:
    typedef uint64_t part_type;

    typedef ArrayList<part_type> part_list;

    typedef part_list::size_type size_type;

    typedef size_type exponent_type;

    LongInt();

    LongInt(long long int initial);

    LongInt(unsigned long long int initial);

    LongInt(long int initial);

    LongInt(unsigned long int initial);

    LongInt(int initial);

    LongInt(unsigned int initial);

    LongInt(float initial);

    LongInt(double initial);

    LongInt(long double initial);

    explicit LongInt(const std::string& numerical_string);

    inline explicit operator bool() const { return operator!=(zero()); }

    inline explicit operator int() const { return m_content[0]; }

    inline explicit operator unsigned int() const { return m_content[0]; }

    inline explicit operator long int() const { return m_content[0]; }

    inline explicit operator unsigned long int() const { return m_content[0]; }

    inline explicit operator long long int() const { return m_content[0]; }

    inline explicit operator unsigned long long int() const { return m_content[0]; }

    inline explicit operator float() const;

    inline explicit operator double() const;

    inline explicit operator long double() const;

    LongInt operator~() const;

    LongInt operator-() const;

    LongInt operator+() const;

    LongInt operator+(const LongInt& other) const;

    LongInt operator-(const LongInt& other) const;

    LongInt operator*(const LongInt& other) const;

    LongInt operator/(const LongInt& other) const;

    LongInt operator%(const LongInt& other) const;

    LongInt operator<<(exponent_type shift_offset) const;

    LongInt operator>>(exponent_type shift_offset) const;

    LongInt pow(exponent_type exponent) const;

    LongInt pow_mod(const LongInt& exponent, const LongInt& modulus) const;

    LongInt operator|(const LongInt& other) const;

    LongInt operator^(const LongInt& other) const;

    LongInt operator&(const LongInt& other) const;

    LongInt operator++(int);

    LongInt& operator++();

    LongInt operator--(int);

    LongInt& operator--();

    int compareTo(const LongInt& other) const;

    bool operator<(const LongInt& other) const { return compareTo(other) == -1; }

    bool operator<=(const LongInt& other) const { return compareTo(other) != 1; }

    bool operator==(const LongInt& other) const { return compareTo(other) == 0; }

    bool operator>=(const LongInt& other) const { return compareTo(other) != -1; }

    bool operator>(const LongInt& other) const { return compareTo(other) == 1; }

    bool operator!=(const LongInt& other) const { return compareTo(other) != 0; }

    LongInt& operator+=(const LongInt& other);

    LongInt& operator-=(const LongInt& other);

    LongInt& operator*=(const LongInt& other);

    LongInt& operator/=(const LongInt& other);

    LongInt& operator%=(const LongInt& other);

    LongInt& operator<<=(exponent_type shift_offset);

    LongInt& operator>>=(exponent_type shift_offset);

    LongInt& pow_eq(exponent_type exponent);

    LongInt& pow_mod_eq(const LongInt& exponent, const LongInt& modulus);

    LongInt& operator|=(const LongInt& other);

    LongInt& operator^=(const LongInt& other);

    LongInt& operator&=(const LongInt& other);

    bool is_positive() const;

    LongInt abs() const;

    LongInt mod(const LongInt& modulus) const;

    LongInt mult_inv_mod(const LongInt& modulus) const;

    LongInt add_inv_mod(const LongInt& modulus) const;

    void divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed = true);

    inline LongInt zero() const { return 0; }

    inline LongInt one() const { return 1; }

    inline size_type size() const { return m_content.size(); }

    inline part_type part_at(size_type i) const { return i < size() ? m_content[i] : 0l; }

    static const uint_fast16_t PART_SIZE = sizeof(LongInt::part_type) * CHAR_BIT;

  private:
    inline size_type read_sign(const std::string& numerical_string);

    inline void write_decimal(std::ostream& out) const;

    inline void write_octal(std::ostream& out) const;

    inline void write_hexadecimal(std::ostream& out) const;

    inline void read_decimal(const std::string& numerical_string, size_type start_index);

    inline void read_octal(const std::string& numerical_string, size_type start_index);

    inline void read_hexadecimal(const std::string& numerical_string, size_type start_index);

    inline int uCompareTo(const LongInt& other) const;

    void remove_zeros();

    void pad_zeros(size_type new_size);

    inline void subtract(const LongInt& other);

    inline void add(const LongInt& other);

    bool m_positive;

    part_list m_content;

  };

  LongInt::exponent_type log2(const LongInt& number);

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, bool& keep);

  LongInt::part_list::iterator multiply(const LongInt::part_list::const_iterator& a_begin,
                                                   const LongInt::part_list::const_iterator& a_end,
                                                   const LongInt::part_list::const_iterator& b_begin,
                                                   const LongInt::part_list::const_iterator& b_end,
                                                   const LongInt::part_list::iterator& c_begin,
                                                   const LongInt::part_list::iterator& c_end);


  std::pair<LongInt::part_list::const_iterator, LongInt::part_list::const_iterator> inline calc_xy2(const LongInt::part_list::const_iterator& xy0_begin,
                                                                                                                          const LongInt::part_list::const_iterator& xy0_end,
                                                                                                                          const LongInt::part_list::const_iterator& xy1_begin,
                                                                                                                          const LongInt::part_list::const_iterator& xy1_end,
                                                                                                                          LongInt::part_list::iterator& c_begin,
                                                                                                                          const LongInt::part_list::iterator& c_end);

  void inline add(const LongInt::part_list::iterator& a_begin,
                  const LongInt::part_list::iterator& a_end,
                  const LongInt::part_list::const_iterator& b_begin,
                  const LongInt::part_list::const_iterator& b_end);

  void inline subtract(const LongInt::part_list::iterator& a_begin,
                       const LongInt::part_list::iterator& a_end,
                       const LongInt::part_list::const_iterator& b_begin,
                       const LongInt::part_list::const_iterator& b_end,
                       bool exchange = false);

  LongInt::size_type space_usage(LongInt::size_type size_a, LongInt::size_type size_b);

}

#endif // DATASTRUCTURES_LONGINT_H
