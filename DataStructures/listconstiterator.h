#ifndef LISTCONSTITERATOR_H
#define LISTCONSTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename List>
  ListConstIterator<T, List> operator+(index_type i, const ListConstIterator<T, List>& it);

  template <typename T, typename List>
  class ListConstIterator : public BaseIterator<T>
  {
    friend ListConstIterator<T, List> operator+ <> (index_type i, const ListConstIterator<T, List>& it);
  public:
    ListConstIterator(const List* list, index_type index = 0);
    ListConstIterator(const ListIterator<T, List>& other);
    ListConstIterator(const ListConstIterator<T, List>& other);
    difference_type operator-(const ListIterator<T, List>& other) const;
    difference_type operator-(const ListConstIterator<T, List>& other) const;
    ListConstIterator<T, List> operator++(int);
    ListConstIterator<T, List>& operator++();
    ListConstIterator<T, List> operator--(int);
    ListConstIterator<T, List>& operator--();
    ListConstIterator<T, List>& operator=(const ListIterator<T, List>& other);
    ListConstIterator<T, List>& operator=(const ListConstIterator<T, List>& other);
    ListConstIterator<T, List> operator+(index_type i) const;
    ListConstIterator<T, List> operator-(index_type i) const;
    ListConstIterator<T, List>& operator+=(index_type i);
    ListConstIterator<T, List>& operator-=(index_type i);
    const T& operator*() const;
    const T& operator[](index_type i) const;
  private:
    const List* m_list;
  };

  template <typename T, typename List>
  ListConstIterator<T, List>::ListConstIterator(const List* list, index_type index):
    BaseIterator<T>(index),
    m_list(list)
  {
  }

  template <typename T, typename List>
  ListConstIterator<T, List>::ListConstIterator(const ListIterator<T, List>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T, typename List>
  ListConstIterator<T, List>::ListConstIterator(const ListConstIterator<T, List>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T, typename List>
  difference_type ListConstIterator<T, List>::operator-(const ListIterator<T, List>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename List>
  difference_type ListConstIterator<T, List>::operator-(const ListConstIterator<T, List>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename List>
  ListConstIterator<T, List> operator+(index_type index, const ListConstIterator<T, List>& other)
  {
    return other + index;
  }

  template <typename T, typename List>
  ListConstIterator<T, List> ListConstIterator<T, List>::operator++(int)
  {
    ListConstIterator<T, List> old (*this);
    BaseIterator<T>::m_index++;
    return old;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator++()
  {
    ++BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListConstIterator<T, List> ListConstIterator<T, List>::operator--(int)
  {
    ListConstIterator<T, List> old (*this);
    BaseIterator<T>::m_index--;
    return old;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator--()
  {
    --BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator=(const ListIterator<T, List>& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator=(const ListConstIterator<T, List>& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T, typename List>
  ListConstIterator<T, List> ListConstIterator<T, List>::operator+(index_type index) const
  {
    ListConstIterator<T, List> other (*this);
    return other += index;
  }

  template <typename T, typename List>
  ListConstIterator<T, List> ListConstIterator<T, List>::operator-(index_type index) const
  {
    ListConstIterator<T, List> other (*this);
    return other -= index;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    return *this;
  }

  template <typename T, typename List>
  ListConstIterator<T, List>& ListConstIterator<T, List>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    return *this;
  }

  template <typename T, typename List>
  const T& ListConstIterator<T, List>::operator*() const
  {
    return (*m_list)[BaseIterator<T>::m_index];
  }

  template <typename T, typename List>
  const T& ListConstIterator<T, List>::operator[](index_type index) const
  {
    return (*m_list)[BaseIterator<T>::m_index + index];
  }

}

#endif // LISTCONSTITERATOR_H
