#ifndef DATASTRUCTURES_POLYNOMIAL_HPP
#define DATASTRUCTURES_POLYNOMIAL_HPP

#include "arraylist.h"
#include "longint.h"
#include "algebrahelper.h"
#include "ring.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Structure>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T, Structure>& polynomial)
  {
    typename Polynomial<T, Structure>::degree_type deg = polynomial.deg();
    if (deg > 0) {
      out << "(";
      for (typename Polynomial<T, Structure>::size_type i = deg + 1; i > 0;)
      {
        --i;
        const T& coeff = polynomial.m_coefficients[i];
        if (coeff != polynomial.m_structure->zero()) {
          if (i < polynomial.deg()) {
            out << " + ";
          }
          if (i >= 1) {
            if (coeff != polynomial.m_structure->one()) {
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

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure,
                                              const T& element,
                                              size_type degree):
    m_structure (structure),
    m_coefficients (element == structure->zero() ? 0 : degree, structure->zero())
  {
    m_coefficients.push_back(element);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure,
                                              const coefficient_list& coefficients):
    m_structure (structure),
    m_coefficients (coefficients)
  {
    remove_zeros();
  }

  template <typename T, typename Structure>
  template <typename Iterator>
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure,
                                              const Iterator& begin,
                                              const Iterator& end):
    m_structure (structure),
    m_coefficients (begin, end)
  {
    remove_zeros();
  }

  template <typename T, typename Structure>
  inline Polynomial< T, Structure > Polynomial< T, Structure >::zero() const
  {
    return Polynomial(m_structure, m_coefficients[0].zero());
  }

  template <typename T, typename Structure>
  inline Polynomial< T, Structure > Polynomial< T, Structure >::one() const
  {
    return Polynomial(m_structure, m_coefficients[0].one());
  }

  template <typename T, typename Structure>
  inline const typename Polynomial< T, Structure >::ring_type* Polynomial< T, Structure >::ring() const
  {
    return new ring_type(zero(), one());
  }

  template <typename T, typename Structure>
  inline T Polynomial<T, Structure>::operator()(const T& value) const
  {
    T result = m_structure->zero();
    for (size_type i = deg() + 1; i > 0;) {
      --i;
      result *= value;
      result += m_coefficients[i];
    }
    return result;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator+() const
  {
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator+(const Polynomial<T, Structure>& other) const
  {
    Polynomial<T, Structure> result (*this);
    return result += other;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator-(const Polynomial<T, Structure>& other) const
  {
    Polynomial<T, Structure> result (*this);
    return result -= other;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator*(const Polynomial<T, Structure>& other) const
  {
    Polynomial<T, Structure> result (*this);
    return result *= other;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator/(const Polynomial<T, Structure>& other) const
  {
    Polynomial<T, Structure> result (*this);
    return result /= other;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator%(const Polynomial<T, Structure>& other) const
  {
    Polynomial<T, Structure> result (*this);
    return result %= other;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::pow(exponent_type exponent) const
  {
    Polynomial<T, Structure> result (*this);
    return result.pow_eq(exponent);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::pow_mod(const LongInt& exponent, const Polynomial<T, Structure>& modulus) const
  {
    Polynomial<T, Structure> result (*this);
    return result.pow_mod_eq(exponent, modulus);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator++(int)
  {
    Polynomial<T, Structure> result (*this); operator++();
    return result;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::operator--(int)
  {
    Polynomial<T, Structure> result (*this); operator--();
    return result;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator++()
  {
    ++m_coefficients[0];
    remove_zeros();
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator--()
  {
    --m_coefficients[0];
    remove_zeros();
    return *this;
  }

  template <typename T, typename Structure>
  inline typename Polynomial<T, Structure>::size_type Polynomial<T, Structure>::size() const
  {
    return m_coefficients.size();
  }

  template <typename T, typename Structure>
  inline typename Polynomial<T, Structure>::size_type Polynomial<T, Structure>::deg() const
  {
    return m_coefficients.size() - 1;
  }

  template <typename T, typename Structure>
  inline const typename Polynomial<T, Structure>::coefficient_list& Polynomial<T, Structure>::coefficients()
  {
    return m_coefficients;
  }

  template <typename T, typename Structure>
  inline bool Polynomial<T, Structure>::operator==(const Polynomial<T, Structure>& other) const
  {
    return m_coefficients == other.m_coefficients;
  }

  template <typename T, typename Structure>
  inline bool Polynomial<T, Structure>::operator!=(const Polynomial<T, Structure>& other) const
  {
    return !operator==(other);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator+=(const Polynomial<T, Structure>& other)
  {
    pad_zeros(other.deg() + 1);
    add(other);
    remove_zeros();
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator-=(const Polynomial<T, Structure>& other)
  {
    pad_zeros(other.deg() + 1);
    subtract(other);
    remove_zeros();
    return *this;
  }

  template <typename T, typename Structure>
  inline void Polynomial<T, Structure>::add(const Polynomial<T, Structure>& other)
  {
    for (size_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] += other.m_coefficients[i];
    }
  }

  template <typename T, typename Structure>
  inline void Polynomial<T, Structure>::subtract(const Polynomial<T, Structure>& other)
  {
    for (size_type i = 0; i <= other.deg(); ++i) {
      m_coefficients[i] -= other.m_coefficients[i];
    }
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator*=(const Polynomial<T, Structure>& other)
  {
    coefficient_list new_coefficients (deg() + other.deg() + 1, 0);
    for (size_type i = 0; i <= deg(); ++i) {
      for (size_type j = 0; j <= other.deg(); ++j) {
        new_coefficients[i + j] += m_coefficients[i] * other.m_coefficients[j];
      }
    }
    m_coefficients = new_coefficients;
    remove_zeros();
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator/=(const Polynomial<T, Structure>& other)
  {
    divide(other, *this, *this);
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>& Polynomial<T, Structure>::operator%=(const Polynomial<T, Structure>& other)
  {
    Polynomial<T, Structure> quotient (m_structure, 0);
    divide(other, quotient, *this);
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::pow_eq(exponent_type exponent)
  {
    const ring_type *r = ring();
    AlgebraHelper::pow_eq(r, *this, exponent);
    delete r;
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::pow_mod_eq(const LongInt& exponent, const Polynomial<T, Structure>& modulus)
  {
    const ring_type *r = ring();
    AlgebraHelper::pow_mod_eq(r, *this, exponent, modulus);
    remove_zeros();
    delete r;
    return *this;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::mod(const Polynomial& modulus) const
  {
    return operator%(modulus);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::mult_inv_mod(const Polynomial<T, Structure>& modulus) const
  {
    const ring_type *r = ring();
    Polynomial<T> inverse = AlgebraHelper::inv_mod(r, mod(modulus), modulus);
    delete r;
    return inverse;
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::add_inv_mod(const Polynomial<T, Structure>& modulus) const
  {
    return operator-().mod(modulus);
  }

  template <typename T, typename Structure>
  inline void Polynomial<T, Structure>::divide(const Polynomial<T, Structure>& divisor, Polynomial<T, Structure>& quotient, Polynomial<T, Structure>& remainder) const
  {
    if (deg() < divisor.deg()) {
      remainder = *this;
      quotient = zero();
      return;
    }
    size_type divisor_deg = divisor.deg();
    size_type new_deg = deg() - divisor_deg;
    remainder = *this;
    if (deg() < divisor_deg) {
      quotient = one();
      return;
    }
    coefficient_list quotient_coefficients (new_deg + 1);
    const T divisor_first_digit = divisor.m_coefficients[divisor_deg];
    for (size_type i = new_deg + 1; i > 0;) {
      --i;
      quotient_coefficients[i] = remainder.m_coefficients[i + divisor_deg] / divisor_first_digit;
      Polynomial<T, Structure> factor (m_structure, quotient_coefficients[i], i);
      Polynomial<T, Structure> back_calculated = factor * divisor;
      remainder.subtract(back_calculated);
    }
    remainder.remove_zeros();
    quotient = Polynomial<T, Structure>(m_structure, quotient_coefficients);
  }

  template <typename T, typename Structure>
  inline void Polynomial<T, Structure>::remove_zeros()
  {
    while (deg() > 0 && m_coefficients.back() == m_structure->zero())
    {
      m_coefficients.pop_back();
    }
  }

  template <typename T, typename Structure>
  inline void Polynomial<T, Structure>::pad_zeros(size_type size)
  {
    for (size_type i = deg(); i < size; ++i) {
      m_coefficients.push_back(m_structure->zero());
    }
  }

}

#endif // DATASTRUCTURES_POLYNOMIAL_HPP
