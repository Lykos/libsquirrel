#ifndef DATASTRUCTURES_LONGINT_H
#define DATASTRUCTURES_LONGINT_H

#include "arraylist.h"
#include "divide.h"
#include "platform.h"
#include <climits>
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

    friend ArrayList<LongArithmetic::part_type>::size_type log2(const LongInt& number);

    friend void LongArithmetic::divide(LongInt &dividend, LongInt &divisor, LongInt &quotient, LongInt &remainder, bool remainder_needed);

    friend class UniformLongIntDistribution;

    friend class LongIntConverter;

  public:
    typedef LongArithmetic::part_type part_type;

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

    inline explicit operator char() const { return m_content[0]; }

    inline explicit operator unsigned char() const { return m_content[0]; }

    inline explicit operator short int() const { return m_content[0]; }

    inline explicit operator unsigned short int() const { return m_content[0]; }

    inline explicit operator int() const { return m_content[0]; }

    inline explicit operator unsigned int() const { return m_content[0]; }

    inline explicit operator long int() const { return m_content[0]; }

    inline explicit operator unsigned long int() const { return m_content[0]; }

    inline explicit operator long long int() const { return m_content[0]; }

    inline explicit operator unsigned long long int() const { return m_content[0]; }

    explicit operator float() const;

    explicit operator double() const;

    explicit operator long double() const;

    LongInt operator~() const;

    LongInt operator-() const;

    LongInt operator+() const;

    LongInt operator+(const LongInt& other) const;

    LongInt operator-(const LongInt& other) const;

    LongInt operator*(const LongInt& other) const;

    LongInt operator/(const LongInt& other) const;

    LongInt operator%(const LongInt& other) const;

    LongInt mod(const LongInt& modulus) const;

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

    LongInt& mod_eq(const LongInt& modulus);

    LongInt& operator<<=(exponent_type shift_offset);

    LongInt& operator>>=(exponent_type shift_offset);

    LongInt& pow_eq(exponent_type exponent);

    LongInt& pow_mod_eq(const LongInt& exponent, const LongInt& modulus);

    LongInt& operator|=(const LongInt& other);

    LongInt& operator^=(const LongInt& other);

    LongInt& operator&=(const LongInt& other);

    bool positive() const { return m_positive; }

    bool positive(bool new_positive) { return m_positive = new_positive; }

    LongInt abs() const;

    LongInt mult_inv_mod(const LongInt& modulus) const;

    LongInt add_inv_mod(const LongInt& modulus) const;

    void divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed = true);

    inline LongInt zero() const { return 0; }

    inline LongInt one() const { return 1; }

    inline size_type size() const { return m_content.size(); }

    inline part_type part_at(size_type i) const { return i < size() ? m_content[i] : 0l; }

    static const uint_fast16_t PART_SIZE = sizeof(part_type) * CHAR_BIT;

    inline const part_list& data() const { return m_content; }

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

}

#endif // DATASTRUCTURES_LONGINT_H
