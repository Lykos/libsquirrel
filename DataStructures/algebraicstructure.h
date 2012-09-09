#ifndef DATASTRUCTURES_ALGEBRAICSTRUCTURE_H
#define DATASTRUCTURES_ALGEBRAICSTRUCTURE_H

namespace DataStructures {
  
  class AlgebraicStructure
  {
  public:
    AlgebraicStructure();

    AlgebraicStructure(const AlgebraicStructure& other);

    AlgebraicStructure(AlgebraicStructure&& other);

    AlgebraicStructure& operator=(const AlgebraicStructure& other);

    AlgebraicStructure& operator=(AlgebraicStructure&& other);

    virtual ~AlgebraicStructure();

    const AlgebraicStructure* polynomials() const;

    virtual const AlgebraicStructure* generate_polynomial_structure() const = 0;

  private:
    mutable const AlgebraicStructure* m_polynomials = 0;

  };
  
} // namespace DataStructures

#endif // DATASTRUCTURES_ALGEBRAICSTRUCTURE_H
