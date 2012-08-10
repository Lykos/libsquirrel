#ifndef ARRAYLISTCONSTITERATOR_H
#define ARRAYLISTCONSTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  ArrayListConstIterator<T> operator+(index_type i, const ArrayListConstIterator<T>& it);

  template <typename T>
  class ArrayListConstIterator : public BaseIterator<T>
  {
    friend ArrayListConstIterator<T> operator+ <> (index_type i, const ArrayListConstIterator<T>& it);
  public:
    ArrayListConstIterator(const ArrayList<T>* list, index_type index = 0);
    ArrayListConstIterator(const ArrayListIterator<T>& other);
    ArrayListConstIterator(const ArrayListConstIterator<T>& other);
    difference_type operator-(const ArrayListIterator<T>& other) const;
    difference_type operator-(const ArrayListConstIterator<T>& other) const;
    ArrayListConstIterator<T> operator++(int);
    ArrayListConstIterator<T>& operator++();
    ArrayListConstIterator<T> operator--(int);
    ArrayListConstIterator<T>& operator--();
    ArrayListConstIterator<T>& operator=(const ArrayListIterator<T>& other);
    ArrayListConstIterator<T>& operator=(const ArrayListConstIterator<T>& other);
    ArrayListConstIterator<T> operator+(index_type i) const;
    ArrayListConstIterator<T> operator-(index_type i) const;
    ArrayListConstIterator<T>& operator+=(index_type i);
    ArrayListConstIterator<T>& operator-=(index_type i);
    const T& operator*() const;
    const T& operator[](index_type i) const;
  private:
    const ArrayList<T>* m_list;
  };

  template <typename T>
  ArrayListConstIterator<T>::ArrayListConstIterator(const ArrayList<T>* list, index_type index):
    BaseIterator<T>(index),
    m_list(list)
  {
  }

  template <typename T>
  ArrayListConstIterator<T>::ArrayListConstIterator(const ArrayListIterator<T>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T>
  ArrayListConstIterator<T>::ArrayListConstIterator(const ArrayListConstIterator<T>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T>
  difference_type ArrayListConstIterator<T>::operator-(const ArrayListIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type ArrayListConstIterator<T>::operator-(const ArrayListConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  ArrayListConstIterator<T> operator+(index_type index, const ArrayListConstIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  ArrayListConstIterator<T> ArrayListConstIterator<T>::operator++(int)
  {
    ArrayListConstIterator<T> old (*this);
    BaseIterator<T>::m_index++;
    return old;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  ArrayListConstIterator<T> ArrayListConstIterator<T>::operator--(int)
  {
    ArrayListConstIterator<T> old (*this);
    BaseIterator<T>::m_index--;
    return old;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator=(const ArrayListConstIterator& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator=(const ArrayListIterator<T>& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T>
  ArrayListConstIterator<T> ArrayListConstIterator<T>::operator+(index_type index) const
  {
    ArrayListConstIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  ArrayListConstIterator<T> ArrayListConstIterator<T>::operator-(index_type index) const
  {
    ArrayListConstIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    return *this;
  }

  template <typename T>
  ArrayListConstIterator<T>& ArrayListConstIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    return *this;
  }

  template <typename T>
  const T& ArrayListConstIterator<T>::operator*() const
  {
    return (*m_list)[BaseIterator<T>::m_index];
  }

  template <typename T>
  const T& ArrayListConstIterator<T>::operator[](index_type index) const
  {
    return (*m_list)[BaseIterator<T>::m_index + index];
  }

}

#endif // ARRAYLISTCONSTITERATOR_H
