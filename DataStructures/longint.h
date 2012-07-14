#ifndef LONGINT_H
#define LONGINT_H

#include "DataStructures_global.h"
#include "arraylist.h"
#include <istream>
#include <ostream>

namespace DataStructures {
  class DATASTRUCTURESSHARED_EXPORT LongInt;

  std::ostream& operator<<(std::ostream& out, const LongInt& longInt);

  std::istream& operator>>(std::istream& in, const LongInt& longInt);

  class DATASTRUCTURESSHARED_EXPORT LongInt
  {
    friend std::ostream& operator<<(std::ostream& out, const LongInt& longInt);
    friend std::istream& operator>>(std::istream& in, const LongInt& longInt);
  public:
    typedef unsigned long long int part_type;
    LongInt(long long int initial = 0);
    LongInt(const LongInt& other);
    explicit LongInt(const std::string& numerical_string);
    LongInt operator-() const;
    LongInt operator+() const;
    LongInt operator+(const LongInt& other) const;
    LongInt operator-(const LongInt& other) const;
    LongInt operator*(const LongInt& other) const;
    LongInt operator/(const LongInt& other) const;
    LongInt operator%(const LongInt& other) const;
    LongInt operator<<(index_type shift_offset) const;
    LongInt operator>>(index_type shift_offset) const;
    LongInt pow(index_type other) const;
    LongInt operator|(const LongInt& other) const;
    LongInt operator^(const LongInt& other) const;
    LongInt operator&(const LongInt& other) const;
    LongInt operator++(int);
    LongInt& operator++();
    LongInt operator--(int);
    LongInt& operator--();
    int compareTo(const LongInt& other) const;
    bool operator<(const LongInt& other) const;
    bool operator<=(const LongInt& other) const;
    bool operator==(const LongInt& other) const;
    bool operator>=(const LongInt& other) const;
    bool operator>(const LongInt& other) const;
    bool operator!=(const LongInt& other) const;
    LongInt& operator=(const LongInt& other);
    LongInt& operator+=(const LongInt& other);
    LongInt& operator-=(const LongInt& other);
    LongInt& operator*=(const LongInt& other);
    LongInt& operator/=(const LongInt& other);
    LongInt& operator%=(const LongInt& other);
    LongInt& operator<<=(index_type shift_offset);
    LongInt& operator>>=(index_type shift_offset);
    LongInt& pow_eq(index_type other);
    LongInt& operator|=(const LongInt& other);
    LongInt& operator^=(const LongInt& other);
    LongInt& operator&=(const LongInt& other);
    bool is_positive() const;
    LongInt abs() const;
    static const index_type PART_SIZE = CHAR_BIT * sizeof(part_type) / 2;
  private:
    explicit LongInt(const ArrayList<part_type>& part);
    index_type size() const;
    LongInt lower_part(index_type part_size) const;
    LongInt upper_part(index_type part_size) const;
    int uCompareTo(const LongInt& other) const;
    LongInt two_complement() const;
    std::string to_digit() const;
    void remove_zeros();
    bool m_positive;
    ArrayList<part_type> m_content;
  };

  LongInt::part_type complement_keep(LongInt::part_type part, LongInt::part_type& keep);

  LongInt::part_type upper_half(LongInt::part_type part);

  LongInt::part_type lower_half(LongInt::part_type part);

}
#endif // LONGINT_H
