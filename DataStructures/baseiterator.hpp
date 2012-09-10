#ifndef DATASTRUCTURES_BaseIterator_HPP
#define DATASTRUCTURES_BaseIterator_HPP

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename Container, typename InputIterator>
  inline BaseIterator<T, Container, InputIterator>::BaseIterator(Container* container, size_type index):
    m_container (container),
    m_index (index)
  {}

  template <typename T, typename Container, typename InputIterator>
  inline typename BaseIterator<T, Container, InputIterator>::difference_type
  BaseIterator<T, Container, InputIterator>::operator-(InputIterator other) const
  {
    return m_index - other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator==(InputIterator other) const
  {
    return m_index == other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator!=(InputIterator other) const
  {
    return m_index != other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator>=(InputIterator other) const
  {
    return m_index >= other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator<=(InputIterator other) const
  {
    return m_index <= other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator>(InputIterator other) const
  {
    return m_index > other.m_index;
  }

  template <typename T, typename Container, typename InputIterator>
  inline bool BaseIterator<T, Container, InputIterator>::operator<(InputIterator other) const
  {
    return m_index < other.m_index;
  }

}

#endif // DATASTRUCTURES_BaseIterator_HPP
