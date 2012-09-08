#ifndef DATASTRUCTURES_RING_H
#define DATASTRUCTURES_RING_H

#include "algebraicstructure.h"
#include "preconditionviolation.h"
#include "polynomial.h"

namespace DataStructures {

  template <typename T, typename Structure>
  class Polynomial;

  template <typename T>
  class Ring : public AlgebraicStructure
  {
  public:
    typedef Polynomial< T, Ring <T> > RingPolynomial;

    inline Ring(const T& zero, const T& one): m_zero (zero), m_one (one) {}

    inline T add_inv(const T& element) const;

    inline T mult_inv(const T& element) const;

    inline const T& zero() const { return m_zero; }

    inline const T& one() const { return m_one; }

    inline const AlgebraicStructure* generate_polynomials() const;

  private:
    T m_zero, m_one;

  };

  template <typename T>
  inline T Ring<T>::add_inv(const T& element) const
  {
    return -element;
  }

  template <typename T>
  inline T Ring<T>::mult_inv(const T& element) const
  {
    PREC(NoField, false);
  }

  template <typename T>
  inline const AlgebraicStructure* Ring<T>::generate_polynomials() const
  {
    return this;/*
    RingPolynomial zero (this, m_zero);
    RingPolynomial one (this, m_one);
    return new Ring<RingPolynomial>(zero, one);*/
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_RING_H
