#ifndef INFINITERANDOM_H
#define INFINITERANDOM_H

#include "arraylist.h"

namespace DataStructures {

  class InfiniteRandom
  {
  public:
    InfiniteRandom();
    InfiniteRandom(const InfiniteRandom& other);
    typedef unsigned int part_type;
    part_type part_at(index_type index) const;
    int compareTo(const InfiniteRandom& other) const;
    InfiniteRandom& operator=(const InfiniteRandom& other);
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
