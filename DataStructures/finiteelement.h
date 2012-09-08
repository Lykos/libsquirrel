#ifndef FINITEELEMENT_H
#define FINITEELEMENT_H

#include "finitefield.h"
#include "longint.h"
#include <ostream>

namespace DataStructures {

  template <typename T>
  class FiniteElement;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const FiniteElement<T>& element);

  template <typename T>
  class FiniteElement
  {
    friend std::ostream& operator<< <> (std::ostream& out, const FiniteElement<T>& element);

  public:
    inline FiniteElement(const FiniteField<T>* field, const T& element);

    inline FiniteElement<T> operator-() const;

    inline FiniteElement<T> operator+() const;

    inline FiniteElement<T> operator+(const FiniteElement<T>& other) const;

    inline FiniteElement<T> operator-(const FiniteElement<T>& other) const;

    inline FiniteElement<T> operator*(const FiniteElement<T>& other) const;

    inline FiniteElement<T> operator/(const FiniteElement<T>& other) const;

    inline FiniteElement<T> pow(const LongInt& exponent) const;

    inline FiniteElement<T> operator++(int);

    inline FiniteElement<T>& operator++();

    inline FiniteElement<T> operator--(int);

    inline FiniteElement<T>& operator--();

    inline FiniteElement<T>& operator+=(const FiniteElement<T>& other);

    inline FiniteElement<T>& operator-=(const FiniteElement<T>& other);

    inline FiniteElement<T>& operator*=(const FiniteElement<T>& other);

    inline FiniteElement<T>& operator/=(const FiniteElement<T>& other);

    inline const FiniteElement<T>& pow_eq(const LongInt& exponent);

    inline FiniteElement<T> add_inv() const;

    inline FiniteElement<T> mult_inv() const;

    inline const T& element() const;

    inline bool operator==(const FiniteElement<T>& other) const;

    inline bool operator!=(const FiniteElement<T>& other) const;

  private:
    inline void normalize();

    const FiniteField<T>* m_field;

    T m_element;

  };

}

#include "finiteelement.hpp"

#endif // FINITEELEMENT_H
