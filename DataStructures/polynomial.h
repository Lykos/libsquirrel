#ifndef DATASTRUCTURES_POLYNOMIAL_H
#define DATASTRUCTURES_POLYNOMIAL_H

#include "arraylist.h"
#include "longint.h"
#include "ring.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Structure>
  class Polynomial;

  template <typename T, typename Structure>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T, Structure>& element);

  template <typename T, typename Structure = Ring<T> >
  class Polynomial
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Polynomial<T, Structure>& element);

  public:
    typedef ArrayList<T> coefficient_list;

    typedef typename coefficient_list::size_type size_type;

    typedef typename coefficient_list::difference_type exponent_type;

    typedef Ring< Polynomial< T, Structure > > ring_type;

    // TODO Remove = NULL, this is invalid and only a hack for the tests.
    inline explicit Polynomial(const Structure *structure = NULL,
                               const T& element = T(),
                               size_type degree = 0);

    inline Polynomial(const Structure *structure,
                      const coefficient_list& coefficients);

    template <typename Iterator>
    inline Polynomial(const Structure *structure,
                      const Iterator& begin,
                      const Iterator& end);

    inline Polynomial< T, Structure > zero() const;

    inline Polynomial< T, Structure > one() const;

    inline ring_type ring() const;

    inline T operator()(const T& value) const;

    inline Polynomial<T, Structure> operator-() const;

    inline Polynomial<T, Structure> operator+() const;

    inline Polynomial<T, Structure> operator+(const Polynomial<T, Structure>& other) const;

    inline Polynomial<T, Structure> operator-(const Polynomial<T, Structure>& other) const;

    inline Polynomial<T, Structure> operator*(const Polynomial<T, Structure>& other) const;

    inline Polynomial<T, Structure> operator/(const Polynomial<T, Structure>& other) const;

    inline Polynomial<T, Structure> operator%(const Polynomial<T, Structure>& other) const;

    inline Polynomial<T, Structure> pow(exponent_type exponent) const;

    inline Polynomial<T, Structure> pow_mod(const LongInt& exponent, const Polynomial<T, Structure>& modulus) const;

    inline Polynomial<T, Structure> operator++(int);

    inline Polynomial<T, Structure> operator--(int);

    inline Polynomial<T, Structure>& operator++();

    inline Polynomial<T, Structure>& operator--();

    inline Polynomial<T, Structure>& operator+=(const Polynomial<T, Structure>& other);

    inline Polynomial<T, Structure>& operator-=(const Polynomial<T, Structure>& other);

    inline Polynomial<T, Structure>& operator*=(const Polynomial<T, Structure>& other);

    inline Polynomial<T, Structure>& operator/=(const Polynomial<T, Structure>& other);

    inline Polynomial<T, Structure>& operator%=(const Polynomial<T, Structure>& other);

    inline Polynomial<T, Structure> pow_eq(exponent_type exponent);

    inline Polynomial<T, Structure> pow_mod_eq(const LongInt& exponent, const Polynomial<T, Structure>& modulus);

    inline Polynomial<T, Structure> mod(const Polynomial& modulus) const;

    inline Polynomial<T, Structure> mult_inv_mod(const Polynomial<T, Structure>& modulus) const ;

    inline Polynomial<T, Structure> add_inv_mod(const Polynomial<T, Structure>& modulus) const;

    inline size_type size() const;

    inline size_type deg() const;

    inline const coefficient_list& coefficients();

    inline bool operator==(const Polynomial<T, Structure>& other) const;

    inline bool operator!=(const Polynomial<T, Structure>& other) const;

    inline void divide(const Polynomial<T, Structure>& divisor, Polynomial<T, Structure>& quotient, Polynomial<T, Structure>& remainder) const;

  private:
    inline void add(const Polynomial<T, Structure>& other);

    inline void subtract(const Polynomial<T, Structure>& other);

    inline void remove_zeros();

    inline void pad_zeros(size_type size);

    const Structure* m_structure;

    coefficient_list m_coefficients;

  };

}

#include "polynomial.hpp"

#endif // DATASTRUCTURES_POLYNOMIAL_H
