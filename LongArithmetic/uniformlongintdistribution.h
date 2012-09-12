#ifndef LONGARITHMETIC_UNIFORMLONGINTDISTRIBUTION_H
#define LONGARITHMETIC_UNIFORMLONGINTDISTRIBUTION_H

#include "longint.h"
#include <boost/random/uniform_int_distribution.hpp>
#include <stdexcept>
#include <istream>
#include <ostream>

namespace LongArithmetic {

  class UniformLongIntDistribution;

  std::ostream& operator<<(std::ostream& out, const UniformLongIntDistribution& dist);

  std::istream& operator>>(std::istream& in, UniformLongIntDistribution& dist);

  class UniformLongIntDistribution
  {
  public:
    typedef LongInt result_type;

    explicit UniformLongIntDistribution(result_type min = 0, result_type max = 0);

    inline void reset();

    template <typename Engine>
    result_type operator()(Engine& engine);

    inline result_type min() const;

    inline result_type max() const;

  private:
    result_type m_min, m_max, m_difference;

    LongInt::size_type m_size;

    std::uniform_int_distribution<LongInt::part_type> m_first_distribution;

    std::uniform_int_distribution<LongInt::part_type> m_part_distribution;

  };

}

#include "uniformlongintdistribution.hpp"

#endif // LONGARITHMETIC_UNIFORMLONGINTDISTRIBUTION_H
