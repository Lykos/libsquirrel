#ifndef DATASTRUCTURES_RING_H
#define DATASTRUCTURES_RING_H

#include "algebraicstructure.h"

namespace DataStructures {

  template <typename T>
  class Ring : public AlgebraicStructure
  {
  public:
    inline Ring(const T& zero, const T& one);

    inline T add_inv(const T& element) const;

    inline const T& zero() const;

    inline const T& one() const;

    inline const AlgebraicStructure* generate_polynomial_structure() const;

  private:
    T m_zero;

    T m_one;

  };

} // namespace DataStructures

// This can be defined to solve some dependency cycles.
// But then ring.hpp has to be included manually.
#ifndef DATASTRUCTURES_RING_NO_HPP
#include "ring.hpp"
#endif

#endif // DATASTRUCTURES_RING_H
