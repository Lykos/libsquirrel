#ifndef DATASTRUCTURES_TREECONSTITERATOR_H
#define DATASTRUCTURES_TREECONSTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T>
  TreeConstIterator<T> operator+(index_type i, const TreeConstIterator<T>& it);

  template <typename T>
  class TreeConstIterator : public BaseIterator<T>
  {
    friend TreeConstIterator<T> operator+ <> (index_type i, const TreeConstIterator<T>& it);
    friend class TreeIterator<T>;
  public:
    typedef struct { const TreeNode<T> *node; index_type left_part; } ConstNodeInfo;
    TreeConstIterator(const ArrayList<ConstNodeInfo> &parent_stack = ArrayList<ConstNodeInfo>(), index_type index = 0);
    TreeConstIterator(const TreeIterator<T>& other);
    TreeConstIterator(const TreeConstIterator<T>& other);
    difference_type operator-(const TreeIterator<T>& other) const;
    difference_type operator-(const TreeConstIterator<T>& other) const;
    TreeConstIterator<T> operator++(int);
    TreeConstIterator<T>& operator++();
    TreeConstIterator<T> operator--(int);
    TreeConstIterator<T>& operator--();
    TreeConstIterator<T>& operator=(const TreeConstIterator<T>& other);
    TreeConstIterator<T> operator+(index_type i) const;
    TreeConstIterator<T> operator-(index_type i) const;
    TreeConstIterator<T>& operator+=(index_type i);
    TreeConstIterator<T>& operator-=(index_type i);
    const T& operator*();
    const T& operator[](index_type i);
  private:
    typedef typename TreeIterator<T>::NodeInfo NodeInfo;
    ArrayList<ConstNodeInfo> m_parent_stack;
    inline void local_search();
    inline const TreeNode<T>& node() const { return *m_parent_stack.back().node; }
    inline index_type left_part() const { return m_parent_stack.back().left_part; }
  };

  template <typename T>
  TreeConstIterator<T>::TreeConstIterator(const ArrayList<ConstNodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T>
  TreeConstIterator<T>::TreeConstIterator(const TreeIterator<T>& other):
    BaseIterator<T> (other.m_index)
  {
    for (typename ArrayList<NodeInfo>::const_iterator it = other.m_parent_stack.begin(); it != other.m_parent_stack.end(); ++it) {
      ConstNodeInfo info {(*it).node, (*it).left_part};
      m_parent_stack.push(info);
    }
  }

  template <typename T>
  TreeConstIterator<T>::TreeConstIterator(const TreeConstIterator<T>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T>
  difference_type TreeConstIterator<T>::operator-(const TreeIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  difference_type TreeConstIterator<T>::operator-(const TreeConstIterator<T>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T>
  TreeConstIterator<T> operator+(index_type index, const TreeConstIterator<T>& other)
  {
    return other + index;
  }

  template <typename T>
  TreeConstIterator<T> TreeConstIterator<T>::operator++(int)
  {
    TreeConstIterator<T> old (*this);
    operator++();
    return old;
  }

  template <typename T>
  TreeConstIterator<T>& TreeConstIterator<T>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeConstIterator<T> TreeConstIterator<T>::operator--(int)
  {
    TreeConstIterator<T> old (*this);
    operator--();
    return old;
  }

  template <typename T>
  TreeConstIterator<T>& TreeConstIterator<T>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeConstIterator<T>& TreeConstIterator<T>::operator=(const TreeConstIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T>
  TreeConstIterator<T> TreeConstIterator<T>::operator+(index_type index) const
  {
    TreeConstIterator<T> other (*this);
    return other += index;
  }

  template <typename T>
  TreeConstIterator<T> TreeConstIterator<T>::operator-(index_type index) const
  {
    TreeConstIterator<T> other (*this);
    return other -= index;
  }

  template <typename T>
  TreeConstIterator<T>& TreeConstIterator<T>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T>
  TreeConstIterator<T>& TreeConstIterator<T>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T>
  const T& TreeConstIterator<T>::operator*()
  {
    return m_parent_stack.back().node->get_element();
  }

  template <typename T>
  const T& TreeConstIterator<T>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T>
  inline void TreeConstIterator<T>::local_search()
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

#endif // DATASTRUCTURES_TREECONSTITERATOR_H
