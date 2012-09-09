#include "algebraicstructure.h"

namespace DataStructures {

  AlgebraicStructure::AlgebraicStructure()
  {}

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
