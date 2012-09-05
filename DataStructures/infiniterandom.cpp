#include "infiniterandom.h"

namespace DataStructures {

  InfiniteRandom::InfiniteRandom():
    m_randomness (0)
  {
  }

  InfiniteRandom::InfiniteRandom(const InfiniteRandom& other):
    m_randomness (other.m_randomness)
  {
  }

  InfiniteRandom::InfiniteRandom(InfiniteRandom&& other):
    m_randomness (std::move(other.m_randomness))
  {
  }

  InfiniteRandom::part_type InfiniteRandom::part_at(size_type index) const
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
    size_type index;
    for (index = 0; part_at(index) == other.part_at(index); ++index);
    if (m_randomness[index] < other.m_randomness[index]) {
      return -1;
    } else {
      return 1;
    }
  }

  InfiniteRandom& InfiniteRandom::operator=(InfiniteRandom&& other)
  {
    if (this == &other) {
      return *this;
    }
    m_randomness = std::move(other.m_randomness);
    return *this;
  }

  InfiniteRandom& InfiniteRandom::operator=(const InfiniteRandom& other)
  {
    if (this == &other) {
      return *this;
    }
    m_randomness = other.m_randomness;
    return *this;
  }

}
