#ifndef FINITEELEMENT_HPP
#define FINITEELEMENT_HPP

#include "finiteelement.h"
#include "finitefield.h"
#include "conditiontype.h"
#include "preconditionviolation.h"
#include "longint.h"
#include <ostream>

#define PREC_FIELD(a, b) PREC(DifferentFields, *((a).m_field) == *((b).m_field))

namespace LongArithmetic {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const FiniteElement<T>& element)
  {
    out << "(" << element.m_element << " mod " << element.m_field->modulus() << ")";
    return out;
  }

  template <typename T>
  inline FiniteElement<T>::FiniteElement(const FiniteField<T>* field, const T& element):
    m_field (field),
    m_element (element)
  {}

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator-() const
  {
    return add_inv();
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator+() const
  {
    return *this;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator+(const FiniteElement<T>& other) const
  {
    FiniteElement<T> result (*this);
    return result += other;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator-(const FiniteElement<T>& other) const
  {
    FiniteElement<T> result (*this);
    return result -= other;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator*(const FiniteElement<T>& other) const
  {
    FiniteElement<T> result (*this);
    return result *= other;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator/(const FiniteElement<T>& other) const
  {
    FiniteElement<T> result (*this);
    return result /= other;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::pow(const LongInt& exponent) const
  {
    FiniteElement<T> result (*this);
    return result.pow_eq(exponent);
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator++(int)
  {
    FiniteElement<T> result (*this);
    operator++();
    return result;
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator++()
  {
    return operator+=(m_field->one());
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::operator--(int)
  {
    FiniteElement<T> result (*this);
    operator--();
    return result;
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator--()
  {
    return operator-=(m_field->one());
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator+=(const FiniteElement<T>& other)
  {
    PREC_FIELD(*this, other);
    m_element += other.m_element;
    normalize();
    return *this;
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator-=(const FiniteElement<T>& other)
  {
    PREC_FIELD(*this, other);
    return operator+=(other.add_inv());
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator*=(const FiniteElement<T>& other)
  {
    PREC_FIELD(*this, other);
    m_element *= other.m_element;
    normalize();
    return *this;
  }

  template <typename T>
  inline FiniteElement<T>& FiniteElement<T>::operator/=(const FiniteElement<T>& other)
  {
    PREC_FIELD(*this, other);
    return operator*=(other.mult_inv());
  }

  template <typename T>
  inline const FiniteElement<T>& FiniteElement<T>::pow_eq(const LongInt& exponent)
  {
    m_element.pow_mod_eq(exponent, m_field->modulus());
    normalize();
    return *this;
  }

  template <typename T>
  inline const T& FiniteElement<T>::element() const
  {
    return m_element;
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::add_inv() const
  {
    return FiniteElement<T>(m_field, m_element.add_inv_mod(m_field->modulus()));
  }

  template <typename T>
  inline FiniteElement<T> FiniteElement<T>::mult_inv() const
  {
    return FiniteElement<T>(m_field, m_element.mult_inv_mod(m_field->modulus()));
  }

  template <typename T>
  inline bool FiniteElement<T>::operator==(const FiniteElement<T>& other) const
  {
    PREC_FIELD(*this, other);
    return m_element == other.m_element;
  }

  template <typename T>
  inline bool FiniteElement<T>::operator!=(const FiniteElement<T>& other) const
  {
    return !operator==(other);
  }

  template <typename T>
  inline void FiniteElement<T>::normalize() {
    m_element.mod_eq(m_field->modulus());
  }

}

#endif // FINITEELEMENT_HPP
