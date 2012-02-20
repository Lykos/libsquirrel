#include "infinite_random.h"
#include <cassert>

namespace DataStructures {
  
  InfiniteRandom::InfiniteRandom()
  {
  }
  
  int InfiniteRandom::compareTo(const InfiniteRandom& other) const
  {
    ArrayList<part_type>::index_type i = 0;
    int result = 0; 
    // TODO Overflow
    while (result == 0) {
      extend(i);
      other.extend(i);
      if (data[i] > other.data[i]) {
	result = 1;
      } else if (data[i] < other.data[i]) {
	result = -1;
      } else {
	result = 0;
      }
    }
    return result;
  }


  bool InfiniteRandom::operator<(const InfiniteRandom& other) const
  {
    return compareTo(other) == -1;
  }
  
  bool InfiniteRandom::operator<=(const InfiniteRandom& other) const
  {
    return compareTo(other) == -1;
  }

  bool InfiniteRandom::operator==(const InfiniteRandom& other) const
  {
    return this == &other;
  }

  bool InfiniteRandom::operator>=(const InfiniteRandom& other) const
  {
    return compareTo(other) == 1;
  }
   
  bool InfiniteRandom::operator>(const InfiniteRandom& other) const
  {
    return compareTo(other) == 1;
  }

  void InfiniteRandom::extend(ArrayList<part_type>::index_type size) const
  {
    // TODO random number
  }

  std::ostream& operator<<(std::ostream& out, const InfiniteRandom& infinite_random)
  {
    // TODO hexadecimal output
  }

}
