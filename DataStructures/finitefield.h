#ifndef DATASTRUCTURES_FINITEFIELD_H
#define DATASTRUCTURES_FINITEFIELD_H

#include "DataStructures_global.h"

namespace DataStructures {

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT FiniteField
  {
  public:
    inline explicit FiniteField(const T& modulus): m_modulus (modulus) {}

    inline const T& modulus() const { return m_modulus; }

    inline bool operator==(const FiniteField& other) const { return m_modulus == other.m_modulus; }

    inline bool operator!=(const FiniteField& other) const { return !operator==(other); }

  private:
    T m_modulus;
  };
  
} // namespace DataStructures

#endif // DATASTRUCTURES_FINITEFIELD_H