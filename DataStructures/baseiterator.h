#ifndef BASEITERATOR_H
#define BASEITERATOR_H

#include "basetypes.h"

namespace DataStructures {

  template <typename T>
  class BaseIterator : public std::iterator<std::random_access_iterator_tag, T, difference_type>
  {
  public:
    BaseIterator(index_type index = 0);
    BaseIterator(const BaseIterator<T>& other);
    difference_type operator-(const BaseIterator<T>& other) const;
    bool operator==(const BaseIterator<T>& other) const;
    bool operator!=(const BaseIterator<T>& other) const;
    bool operator>=(const BaseIterator<T>& other) const;
    bool operator<=(const BaseIterator<T>& other) const;
    bool operator>(const BaseIterator<T>& other) const;
    bool operator<(const BaseIterator<T>& other) const;
  protected:
    index_type m_index;
  };

  template <typename T>
  BaseIterator<T>::BaseIterator(index_type index) : m_index(index) {}

  template <typename T>
  BaseIterator<T>::BaseIterator(const BaseIterator<T> &other) : m_index(other.m_index) {}

  template <typename T>
  difference_type BaseIterator<T>::operator-(const BaseIterator<T>& other) const
  {
    return m_index - other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator==(const BaseIterator<T>& other) const
  {
    return m_index == other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator!=(const BaseIterator<T>& other) const
  {
    return m_index != other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator>=(const BaseIterator<T>& other) const
  {
    return m_index >= other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator<=(const BaseIterator<T>& other) const
  {
    return m_index <= other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator>(const BaseIterator<T>& other) const
  {
    return m_index > other.m_index;
  }

  template <typename T>
  bool BaseIterator<T>::operator<(const BaseIterator<T>& other) const
  {
    return m_index < other.m_index;
  }

}

#endif // BASEITERATOR_H
