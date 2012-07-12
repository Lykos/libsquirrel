#ifndef INFINITERANDOM_H
#define INFINITERANDOM_H

#include "DataStructures_global.h"
#include "arraylist.h"
#include <ostream>

namespace DataStructures {
  class DATASTRUCTURESSHARED_EXPORT InfiniteRandom;

  std::ostream& operator>>(std::ostream& out, const InfiniteRandom& infinite_random);

  class DATASTRUCTURESSHARED_EXPORT InfiniteRandom
  {
    friend std::ostream& operator<<(std::ostream& out, const InfiniteRandom& infinite_random);
  public:
    InfiniteRandom();
    int compareTo(const InfiniteRandom& other) const;
    bool operator<(const InfiniteRandom& other) const;
    bool operator<=(const InfiniteRandom& other) const;
    bool operator==(const InfiniteRandom& other) const;
    bool operator>=(const InfiniteRandom& other) const;
    bool operator>(const InfiniteRandom& other) const;
  private:
    void extend(ArrayList<part_type>::index_type size) const;
    typedef long long int part_type;
    modifiable ArrayList<part_type> data;
  };
}

#endif // INFINITERANDOM_H
