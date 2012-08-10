#ifndef ARRAYLISTITERATOR_H
#define ARRAYLISTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  ArrayListIterator<T> operator+(index_type i, const ArrayListIterator<T>& it);

  template <typename T>
  class ArrayListIterator : public BaseIterator<T>
  {
    friend ArrayListIterator<T> operator+ <> (index_type i, const ArrayListIterator<T>& it);
    friend class ArrayListConstIterator<T>;
  public:
    ArrayListIterator(ArrayList<T>* list, index_type index = 0);
    ArrayListIterator(const ArrayListIterator<T>& other);
    difference_type operator-(const ArrayListIterator<T>& other) const;
    difference_type operator-(const ArrayListConstIterator<T>& other) const;
    ArrayListIterator<T> operator++(int);
    ArrayListIterator<T>& operator++();
    ArrayListIterator<T> operator--(int);
    ArrayListIterator<T>& operator--();
    ArrayListIterator<T>& operator=(const ArrayListIterator<T>& other);
    ArrayListIterator<T> operator+(index_type i) const;
    ArrayListIterator<T> operator-(index_type i) const;
    ArrayListIterator<T>& operator+=(index_type i);
    ArrayListIterator<T>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    ArrayList<T>* m_list;
  };

  template <typename T>
  ArrayListIterator<T>::ArrayListIterator(ArrayList<T>* list, index_type index):
    BaseIterator<T>(index),
    m_list(list)
  {
  }

  template <typename T>
  ArrayListIterator<T>::ArrayListIterator(const ArrayListIterator<T>& other):
    BaseIterator<T>(other.m_index),
    m_list(other.m_list)
  {
  }

  template <typename T>
  difference_type ArrayListIterator<T>::operator-(const ArrayListIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type ArrayListIterator<T>::operator-(const ArrayListConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  ArrayListIterator<T> operator+(index_type index, const ArrayListIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  ArrayListIterator<T> ArrayListIterator<T>::operator++(int)
  {
    ArrayListIterator<T> old (*this);
    BaseIterator<T>::m_index++;
    return old;
  }

  template <typename T>
  ArrayListIterator<T>& ArrayListIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  ArrayListIterator<T> ArrayListIterator<T>::operator--(int)
  {
    ArrayListIterator<T> old (*this);
    BaseIterator<T>::m_index--;
    return old;
  }

  template <typename T>
  ArrayListIterator<T>& ArrayListIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  ArrayListIterator<T>& ArrayListIterator<T>::operator=(const ArrayListIterator& other)
  {
    m_list = other.m_list;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T>
  ArrayListIterator<T> ArrayListIterator<T>::operator+(index_type index) const
  {
    ArrayListIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  ArrayListIterator<T> ArrayListIterator<T>::operator-(index_type index) const
  {
    ArrayListIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  ArrayListIterator<T>& ArrayListIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    return *this;
  }

  template <typename T>
  ArrayListIterator<T>& ArrayListIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    return *this;
  }

  template <typename T>
  T& ArrayListIterator<T>::operator*()
  {
    return (*m_list)[BaseIterator<T>::m_index];
  }

  template <typename T>
  T& ArrayListIterator<T>::operator[](index_type index)
  {
    return (*m_list)[BaseIterator<T>::m_index + index];
  }

}

#endif // ARRAYLISTITERATOR_H
