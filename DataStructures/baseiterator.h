#ifndef DATASTRUCTURES_BASEITERATOR_H
#define DATASTRUCTURES_BASEITERATOR_H

namespace DataStructures {

  template <typename T, typename Container, typename Iterator>
  class BaseIterator : public std::iterator<std::random_access_iterator_tag, T, typename Container::difference_type>
  {
  public:
    typedef typename Container::size_type size_type;

    typedef typename Container::difference_type difference_type;

    inline explicit BaseIterator(Container* container, size_type index = 0);

    inline difference_type operator-(const Iterator& other) const;

    inline bool operator==(const Iterator& other) const;

    inline bool operator!=(const Iterator& other) const;

    inline bool operator>=(const Iterator& other) const;

    inline bool operator<=(const Iterator& other) const;

    inline bool operator>(const Iterator& other) const;

    inline bool operator<(const Iterator& other) const;

  protected:
    Container* m_container;

    size_type m_index;

  };

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

#endif // DATASTRUCTURES_BASEITERATOR_H
