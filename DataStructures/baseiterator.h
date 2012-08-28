#ifndef DATASTRUCTURES_BASEITERATOR_H
#define DATASTRUCTURES_BASEITERATOR_H

#include "basetypes.h"

namespace DataStructures {

  template <typename T, typename Container, typename Iterator>
  class BaseIterator : public std::iterator<std::random_access_iterator_tag, T, difference_type>
  {
  public:
    explicit BaseIterator(Container* container, index_type index = 0);

    inline difference_type operator-(const Iterator& other) const;

    inline bool operator==(const Iterator& other) const;

    inline bool operator!=(const Iterator& other) const;

    inline bool operator>=(const Iterator& other) const;

    inline bool operator<=(const Iterator& other) const;

    inline bool operator>(const Iterator& other) const;

    inline bool operator<(const Iterator& other) const;

  protected:
    Container* m_container;

    index_type m_index;

  };

  template <typename T, typename Container, typename Iterator>
  BaseIterator<T, Container, Iterator>::BaseIterator(Container* container, index_type index):
    m_container (container),
    m_index (index)
  {}

  template <typename T, typename Container, typename Iterator>
  difference_type BaseIterator<T, Container, Iterator>::operator-(const Iterator& other) const
  {
    return m_index - other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator==(const Iterator& other) const
  {
    return m_index == other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator!=(const Iterator& other) const
  {
    return m_index != other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator>=(const Iterator& other) const
  {
    return m_index >= other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator<=(const Iterator& other) const
  {
    return m_index <= other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator>(const Iterator& other) const
  {
    return m_index > other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  bool BaseIterator<T, Container, Iterator>::operator<(const Iterator& other) const
  {
    return m_index < other.m_index;
  }

}

#endif // DATASTRUCTURES_BASEITERATOR_H
