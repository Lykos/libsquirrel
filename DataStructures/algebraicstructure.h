#ifndef DATASTRUCTURES_ALGEBRAICSTRUCTURE_H
#define DATASTRUCTURES_ALGEBRAICSTRUCTURE_H

namespace DataStructures {
  
  class AlgebraicStructure
  {
  public:
    inline AlgebraicStructure() {}

    inline AlgebraicStructure(const AlgebraicStructure& other);

    inline AlgebraicStructure(AlgebraicStructure&& other);

    inline AlgebraicStructure& operator=(const AlgebraicStructure& other);

    inline AlgebraicStructure& operator=(AlgebraicStructure&& other);

    virtual ~AlgebraicStructure();

    inline const AlgebraicStructure* polynomials() const;

  protected:
    virtual const AlgebraicStructure* generate_polynomials() const = 0;

  private:
    mutable const AlgebraicStructure* m_polynomials = 0;

  };

  inline AlgebraicStructure::AlgebraicStructure(const AlgebraicStructure& other)
  {
    // Do NOT copy the polynomials, this is done lazily
  }

  inline AlgebraicStructure::AlgebraicStructure(AlgebraicStructure&& other):
    m_polynomials (other.m_polynomials)
  {
    other.m_polynomials = 0;
  }

  inline AlgebraicStructure& AlgebraicStructure::operator=(const AlgebraicStructure& other)
  {
    delete m_polynomials;
    m_polynomials = 0;
    return *this;
  }

  inline AlgebraicStructure& AlgebraicStructure::operator=(AlgebraicStructure&& other)
  {
    m_polynomials = other.m_polynomials;
    other.m_polynomials = 0;
    return *this;
  }

  inline AlgebraicStructure::~AlgebraicStructure()
  {
    delete m_polynomials;
  }

  inline const AlgebraicStructure* AlgebraicStructure::polynomials() const
  {
    if (m_polynomials == 0) {
      m_polynomials = generate_polynomials();
    }
    return m_polynomials;
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_ALGEBRAICSTRUCTURE_H
