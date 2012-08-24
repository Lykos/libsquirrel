#ifndef FINITEELEMENT_H
#define FINITEELEMENT_H

#include "DataStructures_global.h"
#include "finitefield.h"
#include <stdexcept>
#include <ostream>

#ifndef NDEBUG
#define assert_same_field(other) if (*m_field != *(other.m_field)) { throw new std::logic_error("Operation not allowed for elements of different fields."); }
#else
#define assert_same_field(other)
#endif

namespace DataStructures {

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT FiniteElement;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const FiniteElement<T>& element);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT FiniteElement
  {
    friend std::ostream& operator<< <> (std::ostream& out, const FiniteElement<T>& element);

  public:
    inline FiniteElement(const FiniteField<T>* field, const T& element): m_field (field), m_element (element) {}

    inline FiniteElement<T> operator-() const { FiniteElement<T> other (m_field, m_element); }

    inline FiniteElement<T> operator+() const { return *this; }

    inline FiniteElement<T> operator+(const FiniteElement<T>& other) const { FiniteElement<T> result (*this); return result += other; }

    inline FiniteElement<T> operator-(const FiniteElement<T>& other) const { FiniteElement<T> result (*this); return result -= other; }

    inline FiniteElement<T> operator*(const FiniteElement<T>& other) const { FiniteElement<T> result (*this); return result *= other; }

    inline FiniteElement<T> operator/(const FiniteElement<T>& other) const { FiniteElement<T> result (*this); return result /= other; }

    inline FiniteElement<T> pow(const LongInt& exponent) const { FiniteElement<T> result (*this); return result.pow_eq(exponent); }

    inline FiniteElement<T> operator++(int) { FiniteElement<T> result (*this); operator++(); return result; }

    inline FiniteElement<T>& operator++() { m_element += m_field->modulus().one(); return *this; }

    inline FiniteElement<T> operator--(int) { FiniteElement<T> result (*this); operator--(); return result; }

    inline FiniteElement<T>& operator--() { m_element -= m_field->modulus().one(); return *this; }

    inline FiniteElement<T>& operator+=(const FiniteElement<T>& other) { m_element += other.m_element; normalize(); return *this; }

    inline FiniteElement<T>& operator-=(const FiniteElement<T>& other) { return operator+=(-other); }

    inline FiniteElement<T>& operator*=(const FiniteElement<T>& other) { m_element *= other.m_element; normalize(); return *this; }

    inline FiniteElement<T>& operator/=(const FiniteElement<T>& other) { return operator*=(other.mult_inv()); }

    inline const FiniteElement<T>& pow_eq(const LongInt& exponent) { m_element.pow_mod_eq(exponent, m_field->modulus()); normalize(); return *this; }

    inline FiniteElement<T> mult_inv() const { return FiniteElement<T>(m_field, m_element.mult_inv_mod(m_field->modulus())); }

    inline const T& element() const { return m_element; }

    inline bool operator==(const FiniteElement<T>& other) const { return m_field == other.m_field && m_element == other.m_element; }

    inline bool operator!=(const FiniteElement<T>& other) const { return !operator==(other); }

    inline FiniteElement<T> zero() const { return FiniteElement<T>(m_field, m_element.zero()); }

    inline FiniteElement<T> one() const { return FiniteElement<T>(m_field, m_element.one()); }

  private:
    inline void normalize() { m_element %= m_field->modulus(); if (m_element < 0) { m_element += m_field->modulus(); } }

    const FiniteField<T>* m_field;

    T m_element;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const FiniteElement<T>& element)
  {
    out << "(" << element.m_element << " mod " << element.m_field->modulus() << ")";
    return out;
  }

}

#endif // FINITEELEMENT_H
