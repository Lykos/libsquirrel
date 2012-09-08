#ifndef DATASTRUCTURES_POLYNOMIAL_H
#define DATASTRUCTURES_POLYNOMIAL_H

#include "incompletetypes.h"
#include "arraylist.h"
#include "longint.h"
#include "algebrahelper.h"
#include "ring.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Structure>
  class Polynomial;

  template <typename T, typename Structure>
  inline std::ostream& operator<<(std::ostream& out, const Polynomial<T, Structure>& element);

  template <typename T, typename Structure >
  class Polynomial
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Polynomial<T, Structure>& element);

  public:
    typedef ArrayList<T> coefficient_list;

    typedef typename coefficient_list::size_type size_type;

    typedef typename coefficient_list::difference_type exponent_type;

    inline Polynomial(const Structure *structure = NULL, const T& element = T(), size_type degree = 0);

    inline Polynomial(const Structure *structure, const coefficient_list& coefficients);

    template <typename Iterator>
    inline Polynomial(const Structure *structure, const Iterator& begin, const Iterator& end);

    inline const Polynomial<T, Structure>& zero() const;

    inline const Polynomial<T, Structure>& one() const;

    inline const Ring< Polynomial<T, Structure> >* ring() const;

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

    inline size_type size() const { return m_coefficients.size(); }

    inline size_type deg() const { return m_coefficients.size() - 1; }

    inline const coefficient_list& coefficients() { return m_coefficients; }

    inline bool operator==(const Polynomial<T, Structure>& other) const { return m_coefficients == other.m_coefficients; }

    inline bool operator!=(const Polynomial<T, Structure>& other) const { return !operator==(other); }

    inline void divide(const Polynomial<T, Structure>& divisor, Polynomial<T, Structure>& quotient, Polynomial<T, Structure>& remainder) const;

  private:
    inline void add(const Polynomial<T, Structure>& other);

    inline void subtract(const Polynomial<T, Structure>& other);

    inline void remove_zeros();

    inline void pad_zeros(size_type size);

    const Structure* m_structure;

    coefficient_list m_coefficients;

  };

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
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure, const T& element, size_type degree):
    m_structure (structure),
    m_coefficients (element == structure->zero() ? 0 : degree, structure->zero())
  {
    m_coefficients.push_back(element);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure, const coefficient_list& coefficients):
    m_structure (structure),
    m_coefficients (coefficients)
  {
    remove_zeros();
  }

  template <typename T, typename Structure>
  template <typename Iterator>
  inline Polynomial<T, Structure>::Polynomial(const Structure *structure, const Iterator& begin, const Iterator& end):
    m_structure (structure),
    m_coefficients ()
  {
    m_coefficients.push_all(begin, end);
    remove_zeros();
  }

  template <typename T, typename Structure>
  inline const Polynomial<T, Structure>& Polynomial<T, Structure>::zero() const
  {
    return ring()->zero();
  }

  template <typename T, typename Structure>
  inline const Polynomial<T, Structure>& Polynomial<T, Structure>::one() const
  {
    return ring()->one();
  }

  template <typename T, typename Structure>
  inline const Ring< Polynomial<T, Structure> >* Polynomial<T, Structure>::ring() const
  {
    return static_cast< const Ring< Polynomial<T, Structure> >* >(m_structure->polynomials());
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
    return AlgebraHelper::pow_eq(ring(), *this, exponent);
  }

  template <typename T, typename Structure>
  inline Polynomial<T, Structure> Polynomial<T, Structure>::pow_mod_eq(const LongInt& exponent, const Polynomial<T, Structure>& modulus)
  {
    AlgebraHelper::pow_mod_eq(ring(), *this, exponent, modulus);
    remove_zeros();
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
    return AlgebraHelper::inv_mod(mod(modulus), modulus);
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
    const T divisor_first_inv = m_structure->mult_inv(divisor.m_coefficients[divisor_deg]);
    for (size_type i = new_deg + 1; i > 0;) {
      --i;
      quotient_coefficients[i] = remainder.m_coefficients[i + divisor_deg] * divisor_first_inv;
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

#endif // DATASTRUCTURES_POLYNOMIAL_H
