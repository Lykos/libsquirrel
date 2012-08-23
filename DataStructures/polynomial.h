#ifndef DATASTRUCTURES_POLYNOMIAL_H
#define DATASTRUCTURES_POLYNOMIAL_H

#include "DataStructures_global.h"
#include <ostream>
#include "arraylist.h"
#include "longint.h"
#include "arithmetichelper.h"

namespace DataStructures {

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Polynomial;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T>& element);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Polynomial
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Polynomial<T>& element);

  public:

    explicit inline Polynomial(const T& element): m_coefficients (1, element), m_zero (element.zero()), m_one (element.one()) {}

    inline explicit Polynomial(const ArrayList<T>& coefficients): m_coefficients (coefficients), m_zero (coefficients.front().zero()), m_one (coefficients.front().one()) {}

    template <typename Iterator>
    inline Polynomial(const Iterator& begin, const Iterator& end), m_zero ((*begin).zero()), m_one ((*begin).one())  { m_coefficients.push_all(begin, end); }

    inline Polynomial<T> operator-() const;

    inline Polynomial<T> operator+() const { return *this; }

    inline Polynomial<T> operator+(const Polynomial<T>& other) const { Polynomial<T> result (*this); return result += other; }

    inline Polynomial<T> operator-(const Polynomial<T>& other) const { Polynomial<T> result (*this); return result -= other; }

    inline Polynomial<T> operator*(const Polynomial<T>& other) const { Polynomial<T> result (*this); return result *= other; }

    inline Polynomial<T> operator/(const Polynomial<T>& other) const { Polynomial<T> result (*this); return result /= other; }

    inline Polynomial<T> operator%(const Polynomial<T>& other) const { Polynomial<T> result (*this); return result %= other; }

    inline Polynomial<T> pow(index_type exponent) const { Polynomial<T> result (*this); return result.pow_eq(exponent); }

    inline Polynomial<T> pow_mod(const LongInt& exponent, const Polynomial<T>& modulus) const { Polynomial<T> result (*this); return result.pow_mod_eq(exponent, modulus); }

    inline Polynomial<T> operator++(int) { Polynomial<T> result (*this); operator++(); return result; }

    inline Polynomial<T> operator--(int) { Polynomial<T> result (*this); operator--(); return result; }

    inline Polynomial<T>& operator++();

    inline Polynomial<T>& operator--();

    inline Polynomial<T>& operator+=(const Polynomial<T>& other);

    inline Polynomial<T>& operator-=(const Polynomial<T>& other);

    inline Polynomial<T>& operator*=(const Polynomial<T>& other);

    inline Polynomial<T>& operator/=(const Polynomial<T>& other);

    inline Polynomial<T> pow_eq(index_type exponent);

    inline Polynomial<T> pow_mod_eq(const LongInt& exponent, const Polynomial<T>& modulus);

    inline Polynomial<T> inv_mod(const Polynomial<T>& modulus) const { return DataStructures::inv_mod(*this, modulus); }

    inline index_type deg() const { return m_coefficients.size() - 1; }

    inline const ArrayList<T>& coefficients() { return m_coefficients; }

    inline bool operator==(const Polynomial<T>& other) const { return m_coefficients == other.m_coefficients; }

    inline bool operator!=(const Polynomial<T>& other) const { return !operator==(other); }

    inline void divide(const Polynomial<T>& divisor, Polynomial<T>& quotient, Polynomial<T>& remainder);

    inline Polynomial<T> zero() const { return Polynomial<T>(m_zero); }

    inline Polynomial<T> one() const { return Polynomial<T>(m_one); }

  private:
    inline void remove_zeros() { while (!m_coefficients.is_empty(); m_coefficients.back() == m_zero) { m_coefficients.pop(); } }

    inline void pad_zeros(index_type size) { for (index_type i = deg(); i < size; ++i) { m_coefficients.push(m_zero); } }

    ArrayList<T> m_coefficients;

    T m_zero, m_one;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T>& element)
  {
    out << "(" << element.m_element << " mod " << element.m_field->modulus() << ")";
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator++()
  {
    ++m_coefficients[0];
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator--()
  {
    --m_coefficients[0];
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& other)
  {
    pad_zeros(other.deg() + 1);
    for (index_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] += other.m_coefficients[i];
    }
    remove_zeros();
    return *this;
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& other)
  {
    pad_zeros(other.deg() + 1);
    for (index_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] -= other.m_coefficients[i];
    }
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other)
  {
    ArrayList<T> new_coefficients (deg() + other.deg() + 1, 0);
    for (index_type i = 0; i <= deg; ++i) {
      for (index_type j = 0; j <= other.deg(); ++j) {
        new_coefficients[i + j] += m_coefficients[i] * m_coefficients[j];
      }
    }
    m_coefficients = new_coefficients;
    remove_zeros();
    return *this;
  }

  inline LongInt& LongInt::operator/=(const LongInt& other)
  {
    divide(other, *this, *this);
  }

  inline LongInt& LongInt::operator%=(const LongInt& other)
  {
    LongInt quotient;
    divide(other, quotient, *this);
    return *this;
  }

  template <typename T>
  inline Polynomial<T> Polynomial<T>::pow_eq(index_type exponent)
  {
    ArithmeticHelper::pow_eq(*this, exponent);
    return *this;
  }

  template <typename T>
  inline Polynomial<T> Polynomial<T>::pow_mod_eq(const LongInt& exponent, const Polynomial<T>& modulus)
  {
    ArithmeticHelper::pow_mod_eq(*this, exponent, modulus);
    return *this;
  }

  template <typename T>
  inline void Polynomial<T>::divide(const Polynomial<T>& divisor, Polynomial<T>& quotient, Polynomial<T>& remainder) const
  {
    index_type new_deg = (deg() > divisor ? deg() - divisor.deg() : 0);
    ArrayList<T> quotient_coefficients (new_deg + 1);
    remainder = *this;
    for (index_type i = new_deg + 1; i > 0;) {
      --i;
      quotient_coefficients[i] = remainder.m_coefficients[i]
    }
  }

}

#endif // DATASTRUCTURES_POLYNOMIAL_H
