#ifndef DATASTRUCTURES_RING_HPP
#define DATASTRUCTURES_RING_HPP

#include "ring.h"
#include "preconditionviolation.h"

namespace DataStructures {

  template <typename T>
  inline Ring<T>::Ring(const T& zero, const T& one):
    m_zero (zero),
    m_one (one)
  {}


  template <typename T>
  inline T Ring<T>::add_inv(const T& element) const
  {
    return -element;
  }

  template <typename T>
  inline const T& Ring<T>::zero() const
  {
    return m_zero;
  }

  template <typename T>
  inline const T& Ring<T>::one() const
  {
    return m_one;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_RING_HPP
