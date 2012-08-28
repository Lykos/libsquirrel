#ifndef DATASTRUCTURES_LISTITERATOR_H
#define DATASTRUCTURES_LISTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename List>
  ListIterator<T, List> operator+(index_type i, const ListIterator<T, List>& it);

  template <typename T, typename List>
  class ListIterator : public BaseIterator<T, List, ListIterator<T, List> >
  {
    friend ListIterator<T, List> operator+ <> (index_type i, const ListIterator<T, List>& it);

  private:
    typedef BaseIterator<T, List, ListIterator<T, List> > BaseIt;

  public:
    ListIterator(List* list, index_type index = 0);

    ListIterator<T, List> operator++(int);

    ListIterator<T, List>& operator++();

    ListIterator<T, List> operator--(int);

    ListIterator<T, List>& operator--();

    ListIterator<T, List> operator+(index_type i) const;

    ListIterator<T, List> operator-(index_type i) const;

    difference_type operator-(const ListIterator<T, List>& other) const;

    ListIterator<T, List>& operator+=(index_type i);

    ListIterator<T, List>& operator-=(index_type i);

    T& operator*() const;

    T& operator[](index_type i) const;

    inline operator ListIterator<T const, List const>() const;
  };

  template <typename T, typename List>
  inline ListIterator<T, List>::operator ListIterator<T const, List const>() const
  {
    return ListIterator<T const, List const>(BaseIt::m_container, BaseIt::m_index);
  }

  template <typename T, typename List>
  ListIterator<T, List>::ListIterator(List* list, index_type index):
    BaseIt (list, index)
  {
  }

  template <typename T, typename List>
  ListIterator<T, List> operator+(index_type index, const ListIterator<T, List>& other)
  {
    return other + index;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator++(int)
  {
    ListIterator<T, List> old (*this);
    BaseIt::m_index++;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator++()
  {
    ++BaseIt::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator--(int)
  {
    ListIterator<T, List> old (*this);
    BaseIt::m_index--;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator--()
  {
    --BaseIt::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator+(index_type index) const
  {
    ListIterator<T, List> other (*this);
    return other += index;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator-(index_type index) const
  {
    ListIterator<T, List> other (*this);
    return other -= index;
  }

  template <typename T, typename List>
  difference_type ListIterator<T, List>::operator-(const ListIterator<T, List>& other) const
  {
    return BaseIt::operator-(other);
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator+=(index_type index)
  {
    BaseIt::m_index += index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator-=(index_type index)
  {
    BaseIt::m_index -= index;
    return *this;
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator*() const
  {
    return (*BaseIt::m_container)[BaseIt::m_index];
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator[](index_type index) const
  {
    return (*BaseIt::m_container)[BaseIt::m_index + index];
  }

}

#endif // DATASTRUCTURES_LISTITERATOR_H
