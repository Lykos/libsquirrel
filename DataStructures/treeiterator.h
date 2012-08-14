#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename Node>
  TreeIterator<T, Node> operator+(index_type i, const TreeIterator<T, Node>& it);

  template <typename T, typename Node>
  class TreeIterator : public BaseIterator<T>
  {
    friend TreeIterator<T, Node> operator+ <> (index_type i, const TreeIterator<T, Node>& it);
    friend class TreeConstIterator<T, Node>;
  public:
    typedef struct { Node<T> *node; index_type left_part; } NodeInfo;
    TreeIterator(const ArrayList<NodeInfo> &parent_stack = ArrayList<NodeInfo>(), index_type index = 0);
    TreeIterator(const TreeIterator<T, Node>& other);
    difference_type operator-(const TreeIterator<T, Node>& other) const;
    difference_type operator-(const TreeConstIterator<T, Node>& other) const;
    TreeIterator<T, Node> operator++(int);
    TreeIterator<T, Node>& operator++();
    TreeIterator<T, Node> operator--(int);
    TreeIterator<T, Node>& operator--();
    TreeIterator<T, Node>& operator=(const TreeIterator<T, Node>& other);
    TreeIterator<T, Node> operator+(index_type i) const;
    TreeIterator<T, Node> operator-(index_type i) const;
    TreeIterator<T, Node>& operator+=(index_type i);
    TreeIterator<T, Node>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    ArrayList<NodeInfo> m_parent_stack;
    inline void local_search();
    inline Node<T>& node() const { return *m_parent_stack.top().node; }
    inline index_type left_part() const { return m_parent_stack.top().left_part; }
  };

  template <typename T, typename Node>
  TreeIterator<T, Node>::TreeIterator(const ArrayList<NodeInfo> &parent_stack, index_type index):
    BaseIterator<T> (index),
    m_parent_stack (parent_stack)
  {
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>::TreeIterator(const TreeIterator<T, Node>& other):
    BaseIterator<T> (other.m_index),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T, typename Node>
  difference_type TreeIterator<T, Node>::operator-(const TreeIterator<T, Node>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Node>
  difference_type TreeIterator<T, Node>::operator-(const TreeConstIterator<T, Node>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node> operator+(index_type index, const TreeIterator<T, Node>& other)
  {
    return other + index;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node> TreeIterator<T, Node>::operator++(int)
  {
    TreeIterator<T, Node> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>& TreeIterator<T, Node>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node> TreeIterator<T, Node>::operator--(int)
  {
    TreeIterator<T, Node> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>& TreeIterator<T, Node>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>& TreeIterator<T, Node>::operator=(const TreeIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node> TreeIterator<T, Node>::operator+(index_type index) const
  {
    TreeIterator<T, Node> other (*this);
    return other += index;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node> TreeIterator<T, Node>::operator-(index_type index) const
  {
    TreeIterator<T, Node> other (*this);
    return other -= index;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>& TreeIterator<T, Node>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  TreeIterator<T, Node>& TreeIterator<T, Node>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Node>
  T& TreeIterator<T, Node>::operator*()
  {
    return m_parent_stack.top().node->get_element();
  }

  template <typename T, typename Node>
  T& TreeIterator<T, Node>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T, typename Node>
  inline void TreeIterator<T, Node>::local_search()
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

#endif // TREEITERATOR_H
