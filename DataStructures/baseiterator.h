#ifndef DATASTRUCTURES_BaseIterator_H
#define DATASTRUCTURES_BaseIterator_H

#include <iterator>

namespace DataStructures {

  template <typename T, typename Container, typename InputIterator>
  class BaseIterator : public std::iterator<std::random_access_iterator_tag, T, typename Container::difference_type>
  {
  public:
    typedef typename Container::size_type size_type;

    typedef typename Container::difference_type difference_type;

    inline explicit BaseIterator(Container* container, size_type index = 0);

    inline difference_type operator-(InputIterator other) const;

    inline bool operator==(InputIterator other) const;

    inline bool operator!=(InputIterator other) const;

    inline bool operator>=(InputIterator other) const;

    inline bool operator<=(InputIterator other) const;

    inline bool operator>(InputIterator other) const;

    inline bool operator<(InputIterator other) const;

  protected:
    Container* m_container;

    size_type m_index;

  };

}

#include "baseiterator.hpp"

#endif // DATASTRUCTURES_BaseIterator_H
