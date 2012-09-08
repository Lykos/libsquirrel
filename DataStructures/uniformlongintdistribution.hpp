#ifndef DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_HPP
#define DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_HPP

#include "uniformlongintdistribution.h"
#include "longint.h"
#include <boost/random/uniform_int_distribution.hpp>
#include <stdexcept>
#include <istream>
#include <ostream>

namespace DataStructures {

  inline void UniformLongIntDistribution::reset()
  {}

  inline UniformLongIntDistribution::result_type UniformLongIntDistribution::min() const
  {
    return m_min;
  }

  inline UniformLongIntDistribution::result_type UniformLongIntDistribution::max() const
  {
    return m_max;
  }

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

#endif // DATASTRUCTURES_UNIFORMLONGINTDISTRIBUTION_HPP
