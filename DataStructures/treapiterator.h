#ifndef TREAPITERATOR_H
#define TREAPITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  TreapIterator<T> operator+(index_type i, const TreapIterator<T>& it);

  template <typename T>
  class TreapIterator : public BaseIterator<T>
  {
    friend TreapIterator<T> operator+ <> (index_type i, const TreapIterator<T>& it);
    friend class TreapConstIterator<T>;
  public:
    TreapIterator(Treap<T>* treap, index_type index = 0);
    TreapIterator(const TreapIterator<T>& other);
    difference_type operator-(const TreapIterator<T>& other) const;
    difference_type operator-(const TreapConstIterator<T>& other) const;
    TreapIterator<T> operator++(int);
    TreapIterator<T>& operator++();
    TreapIterator<T> operator--(int);
    TreapIterator<T>& operator--();
    TreapIterator<T>& operator=(const TreapIterator<T>& other);
    TreapIterator<T> operator+(index_type i) const;
    TreapIterator<T> operator-(index_type i) const;
    TreapIterator<T>& operator+=(index_type i);
    TreapIterator<T>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    Treap<T>* m_treap;
    ArrayList<TreapNode<T> > m_parent_stack;
  };

  template <typename T>
  TreapIterator<T>::TreapIterator(Treap<T>* treap, index_type index):
    BaseIterator<T> (index),
    m_treap (treap)
  {
  }

  template <typename T>
  TreapIterator<T>::TreapIterator(const TreapIterator<T>& other):
    BaseIterator<T> (other.m_index),
    m_treap (other.m_treap)
  {
  }

  template <typename T>
  difference_type TreapIterator<T>::operator-(const TreapIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type TreapIterator<T>::operator-(const TreapConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  TreapIterator<T> operator+(index_type index, const TreapIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  TreapIterator<T> TreapIterator<T>::operator++(int)
  {
    TreapIterator<T> old (*this);
    BaseIterator<T>::m_index++;
    return old;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  TreapIterator<T> TreapIterator<T>::operator--(int)
  {
    TreapIterator<T> old (*this);
    BaseIterator<T>::m_index--;
    return old;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    return *this;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator=(const TreapIterator& other)
  {
    m_treap = other.m_treap;
    BaseIterator<T>::m_index = other.m_index;
    return *this;
  }

  template <typename T>
  TreapIterator<T> TreapIterator<T>::operator+(index_type index) const
  {
    TreapIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  TreapIterator<T> TreapIterator<T>::operator-(index_type index) const
  {
    TreapIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    return *this;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    return *this;
  }

  template <typename T>
  T& TreapIterator<T>::operator*()
  {
    return m_parent_stack.top().get_element();
  }

  template <typename T>
  T& TreapIterator<T>::operator[](index_type index)
  {
    return *(operator+(index));
  }

}

#endif // TREAPITERATOR_H
