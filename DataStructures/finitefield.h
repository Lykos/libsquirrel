#ifndef DATASTRUCTURES_FINITEFIELD_H
#define DATASTRUCTURES_FINITEFIELD_H

#include "ring.h"

namespace DataStructures {

  template <typename T>
  class FiniteField : public Ring<T>
  {
  public:
    inline explicit FiniteField(const T& modulus, const T& zero, const T& one);

    inline const T& modulus() const;

    inline bool operator==(const FiniteField& other) const;

    inline bool operator!=(const FiniteField& other) const;

    inline T add_inv(const T& element) const;

    inline T mult_inv(const T& element) const;

  private:
    T m_modulus;

  };

} // namespace DataStructures

#include "finitefield.hpp"

#endif // DATASTRUCTURES_FINITEFIELD_H
