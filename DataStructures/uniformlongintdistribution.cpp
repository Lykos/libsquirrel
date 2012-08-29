#include "uniformlongintdistribution.h"

namespace DataStructures {

  std::ostream& operator<<(std::ostream& out, const UniformLongIntDistribution& dist)
  {
    return out;
  }

  std::istream& operator>>(std::istream& in, UniformLongIntDistribution& dist)
  {
    return in;
  }

  UniformLongIntDistribution::UniformLongIntDistribution(result_type min, result_type max):
    m_min (min),
    m_max (max),
    m_difference (max - min),
    m_size (m_difference.size()),
    m_first_distribution (0, m_difference.part_at(m_size - 1)),
    m_part_distribution ()
  {
    assert(m_size > 0);
    if (min > max) {
      throw new std::logic_error("Min has to be smaller than max for uniform distributions.");
    }
    assert(m_difference.m_positive);
  }

}
