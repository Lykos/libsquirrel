#ifndef DATASTRUCTURES_BASEITERATOR_H
#define DATASTRUCTURES_BASEITERATOR_H

#include "basetypes.h"

namespace DataStructures {

  template <typename T, typename Container, typename Iterator>
  class BaseIterator : public std::iterator<std::random_access_iterator_tag, T, difference_type>
  {
  public:
    BaseIterator(index_type index = 0);

    BaseIterator(const BaseIterator<T, Container, Iterator>& other);

    difference_type operator-(const Iterator& other) const;

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

    bool operator>=(const Iterator& other) const;

    bool operator<=(const Iterator& other) const;

    bool operator>(const Iterator& other) const;

    bool operator<(const Iterator& other) const;

  protected:
    index_type m_index;
  };

  template <typename T, typename Container, typename Iterator>
  BaseIterator<T, Container, Iterator>::BaseIterator(index_type index) : m_index(index) {}

  template <typename T, typename Container, typename Iterator>
  BaseIterator<T, Container, Iterator>::BaseIterator(const BaseIterator<T, Container, Iterator> &other) : m_index(other.m_index) {}

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
