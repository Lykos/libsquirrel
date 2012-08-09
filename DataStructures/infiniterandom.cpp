#include "infiniterandom.h"

namespace DataStructures {

  InfiniteRandom::InfiniteRandom():
    m_randomness (1, rand())
  {
  }

  InfiniteRandom::part_type part_at(ArrayList<InfiniteRandom::part_type>::index_type index) const
  {
    assert(index <= randomness);
    if (index < m_randomness.size()) {
      return m_randomness[index];
    } else {
      m_randomness.push(rand());
    }
  }

  int InfiniteRandom::compareTo(const InfiniteRandom &other) const
  {
    if (this == &other) {
      return 0;
    }
    ArrayList<part_type>::index_type index;
    for (index = 0; part_at(index) == other.part_at(index); ++index);
    if (m_randomness[index] < other.m_randomness[index]) {
      return -1;
    } else {
      return 1;
    }
  }

  bool InfiniteRandom::operator<(const InfiniteRandom& other) const
  {
    return compareTo(other) == 1;
  }

  bool InfiniteRandom::operator<=(const InfiniteRandom& other) const
  {
    return compareTo(other) != -1;
  }

  bool InfiniteRandom::operator==(const InfiniteRandom& other) const
  {
    return this == &other;
  }

  bool InfiniteRandom::operator>=(const InfiniteRandom& other) const
  {
    return compareTo(other) != 1;
  }

  bool InfiniteRandom::operator>(const InfiniteRandom& other) const
  {
    return compareTo(other) == -1;
  }

  bool InfiniteRandom::operator!=(const InfiniteRandom &other) const
  {
    return this != &other;
  }

}
