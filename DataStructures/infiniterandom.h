#ifndef INFINITERANDOM_H
#define INFINITERANDOM_H

#include "arraylist.h"

namespace DataStructures {

  class InfiniteRandom
  {
  public:
    InfiniteRandom();
    typedef unsigned int part_type;
    part_type part_at(index_type index) const;
    int compareTo(const InfiniteRandom& other) const;
    bool operator<(const InfiniteRandom& other) const;
    bool operator<=(const InfiniteRandom& other) const;
    bool operator==(const InfiniteRandom& other) const;
    bool operator>=(const InfiniteRandom& other) const;
    bool operator>(const InfiniteRandom& other) const;
    bool operator!=(const InfiniteRandom& other) const;

  private:
    mutable ArrayList<part_type> m_randomness;

  };

}

#endif // INFINITERANDOM_H
