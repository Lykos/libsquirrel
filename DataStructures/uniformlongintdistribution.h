#ifndef DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H
#define DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H

#include "longint.h"
#include <boost/random/uniform_int_distribution.hpp>
#include <stdexcept>
#include <istream>
#include <ostream>

namespace DataStructures {

  class UniformLongIntDistribution;

  std::ostream& operator<<(std::ostream& out, const UniformLongIntDistribution& dist);

  std::istream& operator>>(std::istream& in, UniformLongIntDistribution& dist);

  class UniformLongIntDistribution
  {
  public:
    typedef LongInt result_type;

    explicit UniformLongIntDistribution(result_type min = 0, result_type max = 0);

    void reset() {}

    template <typename Engine>
    result_type operator()(Engine& engine);

    inline result_type min() const { return m_min; }

    inline result_type max() const { return m_max; }

  private:
    result_type m_min, m_max, m_difference;

    LongInt::size_type m_size;

    boost::random::uniform_int_distribution<LongInt::part_type> m_first_distribution;

    boost::random::uniform_int_distribution<LongInt::part_type> m_part_distribution;

  };

  template <typename Engine>
  UniformLongIntDistribution::result_type UniformLongIntDistribution::operator()(Engine& engine)
  {
    // Get number in the specified range using rejection sampling. TODO Better algorithm.
    LongInt result (0);
    do {
      result.pad_zeros(m_size);
      result.m_content[m_size - 1] = m_first_distribution(engine);
      for (ulong i = m_size - 1; i > 0;) {
        --i;
        result.m_content[i] = m_part_distribution(engine);
      }
    } while (result > m_difference);
    result.remove_zeros();
    result += m_min;
    return result;
  }

}

#endif // DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_H
