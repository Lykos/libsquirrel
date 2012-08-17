#ifndef DATASTRUCTURES_LISTITERATOR_H
#define DATASTRUCTURES_LISTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename List>
  ListIterator<T, List> operator+(index_type i, const ListIterator<T, List>& it);

  template <typename T, typename List>
  class ListIterator : public BaseIterator<T>
  {
    friend ListIterator<T, List> operator+ <> (index_type i, const ListIterator<T, List>& it);
    friend class ListConstIterator<T, List>;
  public:
    ListIterator(List* list, index_type index = 0);
    ListIterator(const ListIterator<T, List>& other);
    difference_type operator-(const ListIterator<T, List>& other) const;
    difference_type operator-(const ListConstIterator<T, List>& other) const;
    ListIterator<T, List> operator++(int);
    ListIterator<T, List>& operator++();
    ListIterator<T, List> operator--(int);
    ListIterator<T, List>& operator--();
    ListIterator<T, List>& operator=(const ListIterator<T, List>& other);
    ListIterator<T, List> operator+(index_type i) const;
    ListIterator<T, List> operator-(index_type i) const;
    ListIterator<T, List>& operator+=(index_type i);
    ListIterator<T, List>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    List* m_list;
  };

  template <typename T, typename List>
  ListIterator<T, List>::ListIterator(List* list, index_type index):
    BaseIterator<T>(index),
    m_list(list)
  {
  }

  template <typename T, typename List>
  ListIterator<T, List>::ListIterator(const ListIterator<T, List>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T, typename List>
  difference_type ListIterator<T, List>::operator-(const ListIterator<T, List>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename List>
  difference_type ListIterator<T, List>::operator-(const ListConstIterator<T, List>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
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
    BaseIterator<T>::m_index++;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator++()
  {
    ++BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List> ListIterator<T, List>::operator--(int)
  {
    ListIterator<T, List> old (*this);
    BaseIterator<T>::m_index--;
    return old;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator--()
  {
    --BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator=(const ListIterator& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
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
    BaseIterator<T>::m_index += index;
    return *this;
  }

  template <typename T, typename List>
  ListIterator<T, List>& ListIterator<T, List>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    return *this;
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator*()
  {
    return (*m_list)[BaseIterator<T>::m_index];
  }

  template <typename T, typename List>
  T& ListIterator<T, List>::operator[](index_type index)
  {
    return (*m_list)[BaseIterator<T>::m_index + index];
  }

}

#endif // DATASTRUCTURES_LISTITERATOR_H
