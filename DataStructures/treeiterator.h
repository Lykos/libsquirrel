#ifndef DATASTRUCTURES_TREEITERATOR_H
#define DATASTRUCTURES_TREEITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  TreeIterator<T> operator+(index_type i, const TreeIterator<T>& it);

  template <typename T>
  class TreeIterator : public BaseIterator<T>
  {
    friend TreeIterator<T> operator+ <> (index_type i, const TreeIterator<T>& it);
    friend class TreeConstIterator<T>;
  public:
    typedef struct { TreeNode<T> *node; index_type left_part; } NodeInfo;
    TreeIterator(const ArrayList<NodeInfo> &parent_stack = ArrayList<NodeInfo>(), index_type index = 0);
    TreeIterator(const TreeIterator<T>& other);
    difference_type operator-(const TreeIterator<T>& other) const;
    difference_type operator-(const TreeConstIterator<T>& other) const;
    TreeIterator<T> operator++(int);
    TreeIterator<T>& operator++();
    TreeIterator<T> operator--(int);
    TreeIterator<T>& operator--();
    TreeIterator<T>& operator=(const TreeIterator<T>& other);
    TreeIterator<T> operator+(index_type i) const;
    TreeIterator<T> operator-(index_type i) const;
    TreeIterator<T>& operator+=(index_type i);
    TreeIterator<T>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    ArrayList<NodeInfo> m_parent_stack;
    inline void local_search();
    inline TreeNode<T>& node() const { return *m_parent_stack.back().node; }
    inline index_type left_part() const { return m_parent_stack.back().left_part; }
  };

  template <typename T>
  TreeIterator<T>::TreeIterator(const ArrayList<NodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T>
  TreeIterator<T>::TreeIterator(const TreeIterator<T>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T>
  difference_type TreeIterator<T>::operator-(const TreeIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type TreeIterator<T>::operator-(const TreeConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  TreeIterator<T> operator+(index_type index, const TreeIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  TreeIterator<T> TreeIterator<T>::operator++(int)
  {
    TreeIterator<T> old (*this);
    operator++();
    return old;
  }

  template <typename T>
  TreeIterator<T>& TreeIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeIterator<T> TreeIterator<T>::operator--(int)
  {
    TreeIterator<T> old (*this);
    operator--();
    return old;
  }

  template <typename T>
  TreeIterator<T>& TreeIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeIterator<T>& TreeIterator<T>::operator=(const TreeIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T>
  TreeIterator<T> TreeIterator<T>::operator+(index_type index) const
  {
    TreeIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  TreeIterator<T> TreeIterator<T>::operator-(index_type index) const
  {
    TreeIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  TreeIterator<T>& TreeIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeIterator<T>& TreeIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T>
  T& TreeIterator<T>::operator*()
  {
    return m_parent_stack.back().node->get_element();
  }

  template <typename T>
  T& TreeIterator<T>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T>
  inline void TreeIterator<T>::local_search()
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

#endif // DATASTRUCTURES_TREEITERATOR_H
