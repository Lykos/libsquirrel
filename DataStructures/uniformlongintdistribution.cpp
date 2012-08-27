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
    m_size (std::max(m_min.size(), m_max.size())),
    m_sign_bit_index (0),
    m_sign_distribution (),
    m_first_distribution (0, std::max(m_min.part_at(m_size - 1), m_max.part_at(m_size - 1))),
    m_part_distribution ()
  {
    assert(m_size > 0);
    if (min > max) {
      throw new std::logic_error("Min has to be smaller than max for uniform distributions.");
    }
  }

  void UniformLongIntDistribution::reset()
  {
    m_sign_bit_index = 0;
  }

}
