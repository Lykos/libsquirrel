#ifndef DATASTRUCTURES_BASEITERATOR_HPP
#define DATASTRUCTURES_BASEITERATOR_HPP

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename Container, typename Iterator>
  inline BaseIterator<T, Container, Iterator>::BaseIterator(Container* container, size_type index):
    m_container (container),
    m_index (index)
  {}

  template <typename T, typename Container, typename Iterator>
  inline typename BaseIterator<T, Container, Iterator>::difference_type
  BaseIterator<T, Container, Iterator>::operator-(const Iterator& other) const
  {
    return m_index - other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator==(const Iterator& other) const
  {
    return m_index == other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator!=(const Iterator& other) const
  {
    return m_index != other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator>=(const Iterator& other) const
  {
    return m_index >= other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator<=(const Iterator& other) const
  {
    return m_index <= other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator>(const Iterator& other) const
  {
    return m_index > other.m_index;
  }

  template <typename T, typename Container, typename Iterator>
  inline bool BaseIterator<T, Container, Iterator>::operator<(const Iterator& other) const
  {
    return m_index < other.m_index;
  }

}

#endif // DATASTRUCTURES_BASEITERATOR_HPP
