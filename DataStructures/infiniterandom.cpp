#include "infiniterandom.h"

namespace DataStructures {

  InfiniteRandom::InfiniteRandom()
  {
  }

  InfiniteRandom::InfiniteRandom(const InfiniteRandom& other):
    m_randomness (other.m_randomness)
  {
  }

  InfiniteRandom::part_type InfiniteRandom::part_at(index_type index) const
  {
    assert(index <= m_randomness.size());
    if (index == m_randomness.size()) {
      m_randomness.push(rand());
    }
    return m_randomness[index];
  }

  int InfiniteRandom::compareTo(const InfiniteRandom &other) const
  {
    if (this == &other) {
      return 0;
    }
    index_type index;
    for (index = 0; part_at(index) == other.part_at(index); ++index);
    if (m_randomness[index] < other.m_randomness[index]) {
      return -1;
    } else {
      return 1;
    }
  }

  InfiniteRandom& InfiniteRandom::operator=(const InfiniteRandom& other)
  {
    m_randomness = other.m_randomness;
    return *this;
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
