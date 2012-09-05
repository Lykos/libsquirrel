#ifndef DATASTRUCTURES_INFINITERANDOM_H
#define DATASTRUCTURES_INFINITERANDOM_H

#include "arraylist.h"

namespace DataStructures {

  class InfiniteRandom
  {
  public:
    InfiniteRandom();

    InfiniteRandom(const InfiniteRandom& other);

    InfiniteRandom(InfiniteRandom&& other);

    ~InfiniteRandom() {}

    typedef u_int64_t part_type;

    typedef ArrayList<part_type> part_list;

    typedef part_list::size_type size_type;

    part_type part_at(size_type index) const;

    int compareTo(const InfiniteRandom& other) const;

    InfiniteRandom& operator=(InfiniteRandom&& other);

    InfiniteRandom& operator=(const InfiniteRandom& other);

    bool operator<(const InfiniteRandom& other) const { return compareTo(other) == -1; }

    bool operator<=(const InfiniteRandom& other) const { return compareTo(other) != 1; }

    bool operator==(const InfiniteRandom& other) const { return compareTo(other) == 0; }

    bool operator>=(const InfiniteRandom& other) const { return compareTo(other) != -1; }

    bool operator>(const InfiniteRandom& other) const { return compareTo(other) == 1; }

    bool operator!=(const InfiniteRandom& other) const { return compareTo(other) != 0; }

  private:
    mutable ArrayList<part_type> m_randomness;

  };

}

#endif // DATASTRUCTURES_INFINITERANDOM_H
