#ifndef DATASTRUCTURES_LONGINT_H
#define DATASTRUCTURES_LONGINT_H

#include "arraylist.h"
#include "platform.h"
#include "divide.h"
#include "ring.h"
#include <climits>
#include <istream>
#include <ostream>
#include <vector>

namespace DataStructures {

  class LongInt;

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

  std::istream& operator>>(std::istream& in, LongInt& longInt);

  class LongInt
  {
  public:
    typedef LongArithmetic::part_type part_type;

    typedef ArrayList<part_type> part_list;

    typedef part_list::size_type size_type;

    typedef part_list::difference_type exponent_type;

    static const LongInt& zero();

    static const LongInt& one();

    static const Ring<LongInt>& ring();

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

    explicit operator bool() const;

    explicit operator char() const;

    explicit operator unsigned char() const;

    explicit operator short int() const;

    explicit operator unsigned short int() const;

    explicit operator int() const;

    explicit operator unsigned int() const;

    explicit operator long int() const;

    explicit operator unsigned long int() const;

    explicit operator long long int() const;

    explicit operator unsigned long long int() const;

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

    int_fast8_t compare_to(const LongInt& other) const;

    int_fast8_t u_compare_to(const LongInt& other) const;

    bool operator<(const LongInt& other) const { return compare_to(other) == -1; }

    bool operator<=(const LongInt& other) const { return compare_to(other) != 1; }

    bool operator==(const LongInt& other) const { return compare_to(other) == 0; }

    bool operator>=(const LongInt& other) const { return compare_to(other) != -1; }

    bool operator>(const LongInt& other) const { return compare_to(other) == 1; }

    bool operator!=(const LongInt& other) const { return compare_to(other) != 0; }

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

    inline size_type size() const { return m_content.size(); }

    inline part_type part_at(size_type i) const { return i < size() ? m_content[i] : 0l; }

    static const uint_fast16_t PART_SIZE = sizeof(part_type) * CHAR_BIT;

    inline const part_list& data() const { return m_content; }

    friend std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

    friend std::istream& operator>>(std::istream& in, LongInt& longInt);

    friend ArrayList<part_type>::size_type log2(const LongInt& number);

    friend void LongArithmetic::divide(LongInt &dividend,
                                       LongInt &divisor,
                                       LongInt &quotient,
                                       LongInt &remainder,
                                       bool remainder_needed);

    friend class UniformLongIntDistribution;

    friend class LongIntConverter;

  private:
    template <typename FLOAT_TYPE, typename INT_TYPE, int MANTISSA, int EXPONENT, int BIAS>
    inline void convert_from(FLOAT_TYPE f);

    template <typename FLOAT_TYPE, typename INT_TYPE, int MANTISSA, int EXPONENT, int BIAS>
    inline FLOAT_TYPE convert_to() const;

    inline size_type read_sign(const std::string& numerical_string);

    inline void write_decimal(std::ostream& out) const;

    inline void write_octal(std::ostream& out) const;

    inline void write_hexadecimal(std::ostream& out) const;

    inline void read_decimal(const std::string& numerical_string, size_type start_index);

    inline void read_octal(const std::string& numerical_string, size_type start_index);

    inline void read_hexadecimal(const std::string& numerical_string, size_type start_index);

    void remove_zeros();

    void pad_zeros(size_type new_size);

    inline void subtract(const LongInt& other);

    inline void add(const LongInt& other);

    inline void inc();

    inline void dec();

    bool m_positive;

    part_list m_content;

  };

  LongInt::size_type log2(const LongInt& number);

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, bool& keep);

}

#endif // DATASTRUCTURES_LONGINT_H
