#ifndef DATASTRUCTURES_RING_HPP
#define DATASTRUCTURES_RING_HPP

#include "polynomial.h"
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

  template <typename T>
  inline const AlgebraicStructure* Ring<T>::generate_polynomial_structure() const
  {
/*    Polynomial<T> poly_zero (*this, m_zero);
    Polynomial<T> poly_one (*this, m_one);
    return Ring< Polynomial<T> >(poly_zero, poly_one);*/
    return 0;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_RING_HPP
