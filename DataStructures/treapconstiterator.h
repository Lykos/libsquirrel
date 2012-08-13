#ifndef TREAPCONSTITERATOR_H
#define TREAPCONSTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  TreapConstIterator<T> operator+(index_type i, const TreapConstIterator<T>& it);

  template <typename T>
  class TreapConstIterator : public BaseIterator<T>
  {
    friend TreapConstIterator<T> operator+ <> (index_type i, const TreapConstIterator<T>& it);
    friend class TreapIterator<T>;
  public:
    typedef struct { const TreapNode<T> *node; index_type left_part; } ConstNodeInfo;
    TreapConstIterator(const ArrayList<ConstNodeInfo> &parent_stack = ArrayList<ConstNodeInfo>(), index_type index = 0);
    TreapConstIterator(const TreapIterator<T>& other);
    TreapConstIterator(const TreapConstIterator<T>& other);
    difference_type operator-(const TreapIterator<T>& other) const;
    difference_type operator-(const TreapConstIterator<T>& other) const;
    TreapConstIterator<T> operator++(int);
    TreapConstIterator<T>& operator++();
    TreapConstIterator<T> operator--(int);
    TreapConstIterator<T>& operator--();
    TreapConstIterator<T>& operator=(const TreapConstIterator<T>& other);
    TreapConstIterator<T> operator+(index_type i) const;
    TreapConstIterator<T> operator-(index_type i) const;
    TreapConstIterator<T>& operator+=(index_type i);
    TreapConstIterator<T>& operator-=(index_type i);
    const T& operator*();
    const T& operator[](index_type i);
  private:
    typedef typename TreapIterator<T>::NodeInfo NodeInfo;
    ArrayList<ConstNodeInfo> m_parent_stack;
    inline void local_search();
    inline const TreapNode<T>& node() const { return *m_parent_stack.top().node; }
    inline index_type left_part() const { return m_parent_stack.top().left_part; }
  };

  template <typename T>
  TreapConstIterator<T>::TreapConstIterator(const ArrayList<ConstNodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T>
  TreapConstIterator<T>::TreapConstIterator(const TreapIterator<T>& other):
    BaseIterator<T> (other.m_index)
  {
    for (typename ArrayList<NodeInfo>::const_iterator it = other.m_parent_stack.begin(); it != other.m_parent_stack.end(); ++it) {
      ConstNodeInfo info {(*it).node, (*it).left_part};
      m_parent_stack.push(info);
    }
  }

  template <typename T>
  TreapConstIterator<T>::TreapConstIterator(const TreapConstIterator<T>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T>
  difference_type TreapConstIterator<T>::operator-(const TreapIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type TreapConstIterator<T>::operator-(const TreapConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  TreapConstIterator<T> operator+(index_type index, const TreapConstIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  TreapConstIterator<T> TreapConstIterator<T>::operator++(int)
  {
    TreapConstIterator<T> old (*this);
    operator++();
    return old;
  }

  template <typename T>
  TreapConstIterator<T>& TreapConstIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreapConstIterator<T> TreapConstIterator<T>::operator--(int)
  {
    TreapConstIterator<T> old (*this);
    operator--();
    return old;
  }

  template <typename T>
  TreapConstIterator<T>& TreapConstIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreapConstIterator<T>& TreapConstIterator<T>::operator=(const TreapConstIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T>
  TreapConstIterator<T> TreapConstIterator<T>::operator+(index_type index) const
  {
    TreapConstIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  TreapConstIterator<T> TreapConstIterator<T>::operator-(index_type index) const
  {
    TreapConstIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  TreapConstIterator<T>& TreapConstIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T>
  TreapConstIterator<T>& TreapConstIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T>
  const T& TreapConstIterator<T>::operator*()
  {
    return m_parent_stack.top().node->get_element();
  }

  template <typename T>
  const T& TreapConstIterator<T>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T>
  inline void TreapConstIterator<T>::local_search()
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

#endif // TREAPCONSTITERATOR_H
