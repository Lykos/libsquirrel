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
    typedef struct { TreapNode<T> *node; index_type left_part; } NodeInfo;
    TreapIterator(const ArrayList<NodeInfo> &parent_stack = ArrayList<NodeInfo>(), index_type index = 0);
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
    ArrayList<NodeInfo> m_parent_stack;
    inline void local_search();
    inline TreapNode<T>& node() const { return *m_parent_stack.top().node; }
    inline index_type left_part() const { return m_parent_stack.top().left_part; }
  };

  template <typename T>
  TreapIterator<T>::TreapIterator(const ArrayList<NodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T>
  TreapIterator<T>::TreapIterator(const TreapIterator<T>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
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
    operator++();
    return old;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreapIterator<T> TreapIterator<T>::operator--(int)
  {
    TreapIterator<T> old (*this);
    operator--();
    return old;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator=(const TreapIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
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
    local_search();
    return *this;
  }

  template <typename T>
  TreapIterator<T>& TreapIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T>
  T& TreapIterator<T>::operator*()
  {
    return m_parent_stack.top().node->get_element();
  }

  template <typename T>
  T& TreapIterator<T>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T>
  inline void TreapIterator<T>::local_search()
  {
    while (BaseIterator<T>::m_index < left_part() || BaseIterator<T>::m_index >= left_part() + node().size()) {
      if (m_parent_stack.size() > 1) {
        m_parent_stack.pop();
      } else {
        return;
      }
    }
    node().iterator_at(m_parent_stack, BaseIterator<T>::m_index, left_part());
  }

}

#endif // TREAPITERATOR_H
