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
    explicit LongInt(ArrayList<part_type>::const_iterator part_begin, ArrayList<part_type>::const_iterator part_end);
    explicit LongInt(const std::string& numerical_string);
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
    index_type inline size() const;
    LongInt inline lower_part(index_type part_size) const;
    LongInt inline upper_part(index_type part_size) const;
    int inline uCompareTo(const LongInt& other) const;
    void inline remove_zeros();
    void inline pad_zeros(index_type new_size);
    void inline subtract(const LongInt& other);
    void inline add(const LongInt& other);
    part_type inline part_at(index_type i) const;
    bool m_positive;
    ArrayList<part_type> m_content;
  };

  LongInt::part_type inline complement_keep(bool positive, LongInt::part_type part, LongInt::part_type& keep);

  LongInt::part_type inline upper_half(LongInt::part_type part);

  LongInt::part_type inline lower_half(LongInt::part_type part);

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
#endif // LONGINT_H
