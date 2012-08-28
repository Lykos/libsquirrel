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

  public:
    ListIterator(List* list, index_type index = 0);
    ListIterator(const ListIterator<T, List>& other);
    difference_type operator-(const ListIterator<T, List>& other) const;
    ListIterator<T, List> operator++(int);
    ListIterator<T, List>& operator++();
    ListIterator<T, List> operator--(int);
    ListIterator<T, List>& operator--();
    ListIterator<T, List>& operator=(const ListIterator<T, List>& other);
    ListIterator<T, List> operator+(index_type i) const;
    ListIterator<T, List> operator-(index_type i) const;
    ListIterator<T, List>& operator+=(index_type i);
    ListIterator<T, List>& operator-=(index_type i);
    T& operator*() const;
    T& operator[](index_type i) const;

    inline operator ListIterator<T const, List const>() const;
  private:
    List* m_list;
  };

  template <typename T, typename List>
  inline ListIterator<T, List>::operator ListIterator<T const, List const>() const
  {
    return ListIterator<T const, List const>(m_list, BaseIterator<T, List, ListIterator<T, List> >::m_index);
  }

  template <typename T, typename List>
  ListIterator<T, List>::ListIterator(List* list, index_type index):
    BaseIterator<T, List, ListIterator<T, List> >(index),
    m_list(list)
  {
  }

  template <typename T, typename List>
  ListIterator<T, List>::ListIterator(const ListIterator<T, List>& other):
    BaseIterator<T, List, ListIterator<T, List> >(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T, typename List>
  difference_type ListIterator<T, List>::operator-(const ListIterator<T, List>& other) const
  {
    return BaseIterator<T, List, ListIterator<T, List> >::m_index - other.m_index;
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
    BaseIterator<T, List, ListIterator<T, List> >::m_index++;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator++()
  {
    ++BaseIterator<T, List, ListIterator<T, List> >::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator--(int)
  {
    ListIterator<T, List> old (*this);
    BaseIterator<T, List, ListIterator<T, List> >::m_index--;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator--()
  {
    --BaseIterator<T, List, ListIterator<T, List> >::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator=(const ListIterator& other)
  {
    if (this == &other) {
      return *this;
    }
    m_list = other.m_list;
    BaseIterator<T, List, ListIterator<T, List> >::m_index = other.m_index;
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
  ListIterator<T, List>& ListIterator<T, List>::operator+=(index_type index)
  {
    BaseIterator<T, List, ListIterator<T, List> >::m_index += index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator-=(index_type index)
  {
    BaseIterator<T, List, ListIterator<T, List> >::m_index -= index;
    return *this;
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator*() const
  {
    return (*m_list)[BaseIterator<T, List, ListIterator<T, List> >::m_index];
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator[](index_type index) const
  {
    return (*m_list)[BaseIterator<T, List, ListIterator<T, List> >::m_index + index];
  }

}

#endif // DATASTRUCTURES_LISTITERATOR_H
