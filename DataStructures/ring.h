#ifndef DATASTRUCTURES_RING_H
#define DATASTRUCTURES_RING_H

namespace DataStructures {

  template <typename T>
  class Ring
  {
  public:
    inline Ring(const T& zero, const T& one);

    inline T add_inv(const T& element) const;

    inline const T& zero() const;

    inline const T& one() const;

  private:
    T m_zero;

    T m_one;

  };

} // namespace DataStructures

#include "ring.hpp"

#endif // DATASTRUCTURES_RING_H
