#ifndef DATASTRUCTURES_LONGINT_H
#define DATASTRUCTURES_LONGINT_H

#include "DataStructures_global.h"
#include "basetypes.h"
#include "arraylist.h"
#include <istream>
#include <ostream>

namespace DataStructures {

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

  std::istream& operator>>(std::istream& in, LongInt& longInt);

  index_type log2(const LongInt& number);

  class DATASTRUCTURESSHARED_EXPORT LongInt
  {
    friend std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

    friend std::istream& operator>>(std::istream& in, LongInt& longInt);

    friend index_type log2(const LongInt& number);

    friend class UniformLongIntDistribution;

  public:
    typedef u_int64_t part_type;

    typedef struct {
      unsigned int* parts;
      unsigned long int num_parts;
      bool sign;
    } packed_longint_t;

    LongInt();

    LongInt(long long int initial);

    LongInt(unsigned long long int initial);

    LongInt(long int initial);

    LongInt(unsigned long int initial);

    LongInt(int initial);

    LongInt(unsigned int initial);

    explicit LongInt(const packed_longint_t& packed);

    // Assumes that the number is always positive. NOT 2-complement. Little endian format.
    LongInt(const u_int8_t* parts, index_type length);

    explicit LongInt(const std::string& numerical_string);

    inline explicit operator bool() const { return operator!=(zero()); }

    inline explicit operator int() const { return m_content[0]; }

    inline explicit operator unsigned int() const { return m_content[0]; }

    inline explicit operator long int() const { return m_content[0]; }

    inline explicit operator unsigned long int() const { return m_content[0]; }

    inline explicit operator long long int() const { return m_content[0]; }

    inline explicit operator unsigned long long int() const { return m_content[0]; }

    LongInt operator~() const;

    LongInt operator-() const;

    LongInt operator+() const;

    LongInt operator+(const LongInt& other) const;

    LongInt operator-(const LongInt& other) const;

    LongInt operator*(const LongInt& other) const;

    LongInt operator/(const LongInt& other) const;

    LongInt operator%(const LongInt& other) const;

    LongInt operator<<(index_type shift_offset) const;

    LongInt operator>>(index_type shift_offset) const;

    LongInt pow(index_type exponent) const;

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

    LongInt& operator<<=(index_type shift_offset);

    LongInt& operator>>=(index_type shift_offset);

    LongInt& pow_eq(index_type exponent);

    LongInt& pow_mod_eq(const LongInt& exponent, const LongInt& modulus);

    LongInt& operator|=(const LongInt& other);

    LongInt& operator^=(const LongInt& other);

    LongInt& operator&=(const LongInt& other);

    bool is_positive() const;

    LongInt abs() const;

    LongInt mod(const LongInt& modulus) const;

    LongInt mult_inv_mod(const LongInt& modulus) const;

    LongInt add_inv_mod(const LongInt& modulus) const;

    packed_longint_t pack() const;

    inline index_type byte_size() const throw() { return log2(*this) / sizeof(part_type) + 1; }

    index_type write(u_int8_t* dest) const throw();

    static const index_type PART_SIZE = CHAR_BIT * sizeof(part_type);

    void divide(const LongInt& other, LongInt& quotient, LongInt& remainder, bool remainder_needed = true);

    inline LongInt zero() const { return 0; }

    inline LongInt one() const { return 1; }

    inline index_type size() const { return m_content.size(); }

    inline part_type part_at(index_type i) const { return i < size() ? m_content[i] : 0l; }

  private:
    inline index_type read_sign(const std::string& numerical_string);

    inline void write_decimal(std::ostream& out) const;

    inline void write_octal(std::ostream& out) const;

    inline void write_hexadecimal(std::ostream& out) const;

    inline void read_decimal(const std::string& numerical_string, index_type start_index);

    inline void read_octal(const std::string& numerical_string, index_type start_index);

    inline void read_hexadecimal(const std::string& numerical_string, index_type start_index);

    inline int uCompareTo(const LongInt& other) const;

    void remove_zeros();

    void pad_zeros(index_type new_size);

    inline void subtract(const LongInt& other);

    inline void add(const LongInt& other);

    bool m_positive;

    ArrayList<part_type> m_content;

  };

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, bool& keep);

  ArrayList<LongInt::part_type>::iterator multiply(const ArrayList<LongInt::part_type>::const_iterator& a_begin,
                                                   const ArrayList<LongInt::part_type>::const_iterator& a_end,
                                                   const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                                                   const ArrayList<LongInt::part_type>::const_iterator& b_end,
                                                   const ArrayList<LongInt::part_type>::iterator& c_begin,
                                                   const ArrayList<LongInt::part_type>::iterator& c_end);


  std::pair<ArrayList<LongInt::part_type>::const_iterator, ArrayList<LongInt::part_type>::const_iterator> inline calc_xy2(const ArrayList<LongInt::part_type>::const_iterator& xy0_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy0_end,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy1_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::const_iterator& xy1_end,
                                                                                                                          ArrayList<LongInt::part_type>::iterator& c_begin,
                                                                                                                          const ArrayList<LongInt::part_type>::iterator& c_end);

  void inline add(const ArrayList<LongInt::part_type>::iterator& a_begin,
                  const ArrayList<LongInt::part_type>::iterator& a_end,
                  const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                  const ArrayList<LongInt::part_type>::const_iterator& b_end);

  void inline subtract(const ArrayList<LongInt::part_type>::iterator& a_begin,
                       const ArrayList<LongInt::part_type>::iterator& a_end,
                       const ArrayList<LongInt::part_type>::const_iterator& b_begin,
                       const ArrayList<LongInt::part_type>::const_iterator& b_end,
                       bool exchange = false);

  index_type space_usage(index_type size_a, index_type size_b);

}

#endif // DATASTRUCTURES_LONGINT_H
