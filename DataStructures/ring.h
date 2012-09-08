#ifndef DATASTRUCTURES_RING_H
#define DATASTRUCTURES_RING_H

#include "preconditionviolation.h"

namespace DataStructures {

  template <typename T>
  class Ring
  {
  public:
    inline Ring(const T& zero, const T& one): m_zero (zero), m_one (one) {}

    inline T add_inv(const T& element) const;

    inline const T& zero() const { return m_zero; }

    inline const T& one() const { return m_one; }

  private:
    T m_zero;

    T m_one;

  };

  template <typename T>
  inline T Ring<T>::add_inv(const T& element) const
  {
    return -element;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_RING_H
