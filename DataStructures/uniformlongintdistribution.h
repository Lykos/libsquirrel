#ifndef DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H
#define DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H

#include "basetypes.h"
#include "DataStructures_global.h"
#include "longint.h"
#include <boost/random/uniform_int_distribution.hpp>
#include <stdexcept>
#include <istream>
#include <ostream>

namespace DataStructures {

  std::ostream& operator<<(std::ostream& out, const UniformLongIntDistribution& dist);

  std::istream& operator>>(std::istream& in, UniformLongIntDistribution& dist);

  class DATASTRUCTURESSHARED_EXPORT UniformLongIntDistribution
  {
  public:
    typedef LongInt result_type;

    explicit UniformLongIntDistribution(result_type min, result_type max);

    void reset();

    template <typename Engine>
    result_type operator()(Engine& engine);

    inline result_type min() const { return m_min; }

    inline result_type max() const { return m_max; }

  private:
    template <typename Engine>
    bool get_next_sign(Engine& engine);

    result_type m_min, m_max;

    uint m_size, m_sign_bit_index, m_sign_bits;

    std::uniform_int_distribution<uint> m_sign_distribution;

    std::uniform_int_distribution<LongInt::part_type> m_first_distribution;

    std::uniform_int_distribution<LongInt::part_type> m_part_distribution;

  };

  template <typename Engine>
  UniformLongIntDistribution::result_type UniformLongIntDistribution::operator()(Engine& engine)
  {
    // Get number in the specified range using rejection sampling. TODO Better algorithm.
    LongInt result (0);
    do {
      result.pad_zeros(m_size);
      if (!m_min.is_positive() && m_max.is_positive()) {
        result.m_positive = get_next_sign(engine);
      }
      result.m_content[m_size - 1] = m_first_distribution(engine);
      for (uint i = m_size - 1; i > 0;) {
        --i;
        result.m_content[i] = m_part_distribution(engine);
      }
    } while (result < m_min || result > m_max);
    result.remove_zeros();
    return result;
  }

  template <typename Engine>
  bool UniformLongIntDistribution::get_next_sign(Engine& engine)
  {
    if (m_sign_bit_index == 0) {
      m_sign_bit_index = CHAR_BIT * sizeof(uint);
      m_sign_bits = m_sign_distribution(engine);
    }
    return (m_sign_bits >> --m_sign_bit_index) & 1;
  }

}

#endif // DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H
