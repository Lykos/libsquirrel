#ifndef DATASTRUCTURES_FINITEFIELD_H
#define DATASTRUCTURES_FINITEFIELD_H

#include "ring.h"

namespace DataStructures {

  template <typename T>
  class FiniteField : public Ring<T>
  {
  public:
    inline explicit FiniteField(const T& modulus, const T& zero, const T& one);

    inline const T& modulus() const { return m_modulus; }

    inline bool operator==(const FiniteField& other) const { return m_modulus == other.m_modulus; }

    inline bool operator!=(const FiniteField& other) const { return !operator==(other); }

    inline T add_inv(const T& element) const;

    inline T mult_inv(const T& element) const;

  private:
    T m_modulus;

  };

  template <typename T>
  inline FiniteField<T>::FiniteField(const T& modulus, const T& zero, const T& one):
    Ring<T>(zero, one),
    m_modulus (modulus)
  {}

  template <typename T>
  inline T FiniteField<T>::add_inv(const T& element) const
  {
    return element.add_inv_mod(m_modulus);
  }

  template <typename T>
  inline T FiniteField<T>::mult_inv(const T& element) const
  {
    return element.mult_inv_mod(m_modulus);
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FINITEFIELD_H
