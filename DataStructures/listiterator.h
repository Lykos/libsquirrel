#ifndef DATASTRUCTURES_ListIterator_H
#define DATASTRUCTURES_ListIterator_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename List>
  class ListIterator;

  template <typename T, typename List>
  ListIterator<T, List> operator+(typename List::difference_type i, const ListIterator<T, List>& it);

  template <typename T, typename List>
  class ListIterator : public BaseIterator<T, List, ListIterator<T, List> >
  {
    friend ListIterator<T, List> operator+ <> (typename List::difference_type i, const ListIterator<T, List>& it);

  private:
    typedef BaseIterator<T, List, ListIterator<T, List> > BaseIt;

  public:
    typedef typename BaseIterator<T, List, ListIterator<T, List> >::size_type size_type;

    typedef typename BaseIterator<T, List, ListIterator<T, List> >::difference_type difference_type;

    ListIterator(List* list, size_type index = 0);

    ListIterator<T, List> operator++(int);

    ListIterator<T, List>& operator++();

    ListIterator<T, List> operator--(int);

    ListIterator<T, List>& operator--();

    ListIterator<T, List> operator+(difference_type i) const;

    ListIterator<T, List> operator-(difference_type i) const;

    difference_type operator-(const ListIterator<T, List>& other) const;

    ListIterator<T, List>& operator+=(difference_type i);

    ListIterator<T, List>& operator-=(difference_type i);

    T& operator*() const;

    T& operator[](difference_type index) const;

    T* operator->() const;

    inline operator ListIterator<T const, List const>() const;
  };

}

#include "listiterator.hpp"

#endif // DATASTRUCTURES_ListIterator_H
