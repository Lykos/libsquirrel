#ifndef DATASTRUCTURES_FINITEFIELD_HPP
#define DATASTRUCTURES_FINITEFIELD_HPP

#include "finitefield.h"
#include "ring.h"

namespace DataStructures {

  template <typename T>
  inline FiniteField<T>::FiniteField(const T& modulus, const T& zero, const T& one):
    Ring<T>(zero, one),
    m_modulus (modulus)
  {}

  template <typename T>
  inline const T& FiniteField<T>::modulus() const
  {
    return m_modulus;
  }

  template <typename T>
  inline bool FiniteField<T>::operator==(const FiniteField<T>& other) const
  {
    // TODO Same modulus, but different zero/one makes no sense
    return m_modulus == other.m_modulus;
  }

  template <typename T>
  inline bool FiniteField<T>::operator!=(const FiniteField<T>& other) const
  {
    return !operator==(other);
  }

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

#endif // DATASTRUCTURES_FINITEFIELD_HPP
