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
    inline Polynomial() {}

    explicit inline Polynomial(const T& element, index_type degree = 0): m_coefficients (element == element.zero() ? 0 : degree, element.zero()), m_zero (element.zero()), m_one (element.one()) { m_coefficients.push(element); }

    inline explicit Polynomial(const ArrayList<T>& coefficients): m_coefficients (coefficients), m_zero (coefficients.front().zero()), m_one (coefficients.front().one()) { remove_zeros(); }

    template <typename Iterator>
    inline Polynomial(const Iterator& begin, const Iterator& end): m_coefficients (), m_zero ((*begin).zero()), m_one ((*begin).one())  { m_coefficients.push_all(begin, end); remove_zeros(); }

    inline T operator()(const T& value) const;

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

    inline Polynomial<T>& operator%=(const Polynomial<T>& other);

    inline Polynomial<T> pow_eq(index_type exponent);

    inline Polynomial<T> pow_mod_eq(const LongInt& exponent, const Polynomial<T>& modulus);

    inline Polynomial<T> mod(const Polynomial& modulus) const { return operator%(modulus); }

    inline Polynomial<T> mult_inv_mod(const Polynomial<T>& modulus) const { return ArithmeticHelper::inv_mod(mod(modulus), modulus); }

    inline Polynomial<T> add_inv_mod(const Polynomial<T>& modulus) const { return operator-().mod(modulus); }

    inline index_type deg() const { return m_coefficients.size() - 1; }

    inline const ArrayList<T>& coefficients() { return m_coefficients; }

    inline bool operator==(const Polynomial<T>& other) const { return m_coefficients == other.m_coefficients; }

    inline bool operator!=(const Polynomial<T>& other) const { return !operator==(other); }

    inline void divide(const Polynomial<T>& divisor, Polynomial<T>& quotient, Polynomial<T>& remainder) const;

    inline Polynomial<T> zero() const { return Polynomial<T>(m_zero); }

    inline Polynomial<T> one() const { return Polynomial<T>(m_one); }

  private:
    inline void add(const Polynomial<T>& other);

    inline void subtract(const Polynomial<T>& other);

    inline void remove_zeros() { while (deg() > 0 && m_coefficients.back() == m_zero) { m_coefficients.pop(); } }

    inline void pad_zeros(index_type size) { for (index_type i = deg(); i < size; ++i) { m_coefficients.push(m_zero); } }

    ArrayList<T> m_coefficients;

    T m_zero, m_one;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial)
  {
    index_type deg = polynomial.deg();
    if (deg> 0) {
      out << "(";
      for (index_type i = deg + 1; i > 0;)
      {
        --i;
        const T& coeff = polynomial.m_coefficients[i];
        if (coeff != coeff.zero()) {
          if (i < polynomial.deg()) {
            out << " + ";
          }
          if (i >= 1) {
            if (coeff != coeff.one()) {
              out << coeff << " ";
            }
            out << "x";
            if (i > 1) {
              out << "^" << i;
            }
          } else {
            out << coeff;
          }
        }
      }
      out << ")";
    } else {
      out << polynomial.m_coefficients[0];
    }
    return out;
  }

  template <typename T>
  inline T Polynomial<T>::operator()(const T& value) const
  {
    T result = m_zero;
    for (index_type i = deg() + 1; i > 0;) {
      --i;
      result *= value;
      result += m_coefficients[i];
    }
    return result;
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
    add(other);
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& other)
  {
    pad_zeros(other.deg() + 1);
    subtract(other);
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline void Polynomial<T>::add(const Polynomial<T>& other)
  {
    for (index_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] += other.m_coefficients[i];
    }
  }

  template <typename T>
  inline void Polynomial<T>::subtract(const Polynomial<T>& other)
  {
    for (index_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] -= other.m_coefficients[i];
    }
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other)
  {
    ArrayList<T> new_coefficients (deg() + other.deg() + 1, 0);
    for (index_type i = 0; i <= deg(); ++i) {
      for (index_type j = 0; j <= other.deg(); ++j) {
        new_coefficients[i + j] += m_coefficients[i] * other.m_coefficients[j];
      }
    }
    m_coefficients = new_coefficients;
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator/=(const Polynomial<T>& other)
  {
    divide(other, *this, *this);
    return *this;
  }

  template <typename T>
  inline Polynomial<T>& Polynomial<T>::operator%=(const Polynomial<T>& other)
  {
    Polynomial<T> quotient;
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
    remove_zeros();
    return *this;
  }

  template <typename T>
  inline void Polynomial<T>::divide(const Polynomial<T>& divisor, Polynomial<T>& quotient, Polynomial<T>& remainder) const
  {
    if (deg() < divisor.deg()) {
      remainder = *this;
      quotient = zero();
      return;
    }
    index_type divisor_deg = divisor.deg();
    index_type new_deg = deg() - divisor_deg;
    remainder = *this;
    if (deg() < divisor_deg) {
      quotient = one();
      return;
    }
    ArrayList<T> quotient_coefficients (new_deg + 1);
    const T& divisor_first = divisor.m_coefficients[divisor_deg];
    for (index_type i = new_deg + 1; i > 0;) {
      --i;
      quotient_coefficients[i] = remainder.m_coefficients[i + divisor_deg] / divisor_first;
      Polynomial<T> factor (quotient_coefficients[i], i);
      Polynomial<T> back_calculated = factor * divisor;
      remainder.subtract(back_calculated);
    }
    remainder.remove_zeros();
    quotient = Polynomial<T>(quotient_coefficients);
  }

}

#endif // DATASTRUCTURES_POLYNOMIAL_H
