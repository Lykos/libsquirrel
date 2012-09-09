#include "algebraicstructure.h"

namespace DataStructures {

  AlgebraicStructure::AlgebraicStructure()
  {}

  AlgebraicStructure::AlgebraicStructure(const AlgebraicStructure& other)
  {}

  AlgebraicStructure::AlgebraicStructure(AlgebraicStructure&& other):
    m_polynomials (other.m_polynomials)
  {
    other.m_polynomials = 0;
  }

  AlgebraicStructure& AlgebraicStructure::operator=(const AlgebraicStructure& other)
  {
    delete m_polynomials;
    m_polynomials = 0;
    return *this;
  }

  AlgebraicStructure& AlgebraicStructure::operator=(AlgebraicStructure&& other)
  {
    delete m_polynomials;
    m_polynomials = other.m_polynomials;
    other.m_polynomials = 0;
    return *this;
  }

  AlgebraicStructure::~AlgebraicStructure()
  {
    delete m_polynomials;
  }

  const AlgebraicStructure* AlgebraicStructure::polynomials() const
  {
    if (m_polynomials == 0) {
      m_polynomials = generate_polynomial_structure();
    }
    return m_polynomials;
  }

} // namespace DataStructures
