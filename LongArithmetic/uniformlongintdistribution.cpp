#include "uniformlongintdistribution.h"
#include "prec_macro.h"
#include <ostream>
#include <istream>

namespace LongArithmetic {

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
    m_first_distribution (0, m_difference.data()[m_size - 1]),
    m_part_distribution ()
  {
    PREC(InvalidRange, min <= max);
  }

}
