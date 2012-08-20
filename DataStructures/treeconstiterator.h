#ifndef DATASTRUCTURES_TREECONSTITERATOR_H
#define DATASTRUCTURES_TREECONSTITERATOR_H

#include "baseiterator.h"

namespace DataStructures {

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> operator+(index_type i, const TreeConstIterator<T, Tree>& it);

  template <typename T, typename Tree>
  class TreeConstIterator : public BaseIterator<T>
  {
    friend TreeConstIterator<T, Tree> operator+ <> (index_type i, const TreeConstIterator<T, Tree>& it);
    friend class TreeIterator<T, Tree>;
  public:
    typedef struct { const TreeNode<T> *node; index_type left_size; } ConstNodeInfo;
    TreeConstIterator(const Tree* tree, index_type index = 0);
    TreeConstIterator(const TreeIterator<T, Tree>& other);
    TreeConstIterator(const TreeConstIterator<T, Tree>& other);
    difference_type operator-(const TreeIterator<T, Tree>& other) const;
    difference_type operator-(const TreeConstIterator<T, Tree>& other) const;
    TreeConstIterator<T, Tree> operator++(int);
    TreeConstIterator<T, Tree>& operator++();
    TreeConstIterator<T, Tree> operator--(int);
    TreeConstIterator<T, Tree>& operator--();
    TreeConstIterator<T, Tree>& operator=(const TreeConstIterator<T, Tree>& other);
    TreeConstIterator<T, Tree> operator+(index_type i) const;
    TreeConstIterator<T, Tree> operator-(index_type i) const;
    TreeConstIterator<T, Tree>& operator+=(index_type i);
    TreeConstIterator<T, Tree>& operator-=(index_type i);
    const T& operator*();
    const T& operator[](index_type i);
  private:
    typedef typename TreeIterator<T, Tree>::NodeInfo NodeInfo;
    const Tree* m_tree;
    ArrayList<ConstNodeInfo> m_parent_stack;
    inline void local_search();
    inline const TreeNode<T>& node() const { return *m_parent_stack.back().node; }
    inline index_type left_size() const { return m_parent_stack.back().left_size; }
  };

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>::TreeConstIterator(const Tree* tree, index_type index):
    BaseIterator<T> (index),
    m_tree (tree),
    m_parent_stack (0)
  {
    local_search();
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>::TreeConstIterator(const TreeIterator<T, Tree>& other):
    BaseIterator<T> (other.m_index),
    m_tree (other.m_tree)
  {
    for (typename ArrayList<NodeInfo>::const_iterator it = other.m_parent_stack.begin(); it != other.m_parent_stack.end(); ++it) {
      ConstNodeInfo info {(*it).node, (*it).left_size};
      m_parent_stack.push(info);
    }
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>::TreeConstIterator(const TreeConstIterator<T, Tree>& other):
    BaseIterator<T> (other.m_index),
    m_tree (other.m_tree),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T, typename Tree>
  difference_type TreeConstIterator<T, Tree>::operator-(const TreeIterator<T, Tree>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Tree>
  difference_type TreeConstIterator<T, Tree>::operator-(const TreeConstIterator<T, Tree>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> operator+(index_type index, const TreeConstIterator<T, Tree>& other)
  {
    return other + index;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> TreeConstIterator<T, Tree>::operator++(int)
  {
    TreeConstIterator<T, Tree> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>& TreeConstIterator<T, Tree>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> TreeConstIterator<T, Tree>::operator--(int)
  {
    TreeConstIterator<T, Tree> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>& TreeConstIterator<T, Tree>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>& TreeConstIterator<T, Tree>::operator=(const TreeConstIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> TreeConstIterator<T, Tree>::operator+(index_type index) const
  {
    TreeConstIterator<T, Tree> other (*this);
    return other += index;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree> TreeConstIterator<T, Tree>::operator-(index_type index) const
  {
    TreeConstIterator<T, Tree> other (*this);
    return other -= index;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>& TreeConstIterator<T, Tree>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeConstIterator<T, Tree>& TreeConstIterator<T, Tree>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  const T& TreeConstIterator<T, Tree>::operator*()
  {
    return m_parent_stack.back().node->get_element();
  }

  template <typename T, typename Tree>
  const T& TreeConstIterator<T, Tree>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T, typename Tree>
  inline void TreeConstIterator<T, Tree>::local_search()
  {
    if (BaseIterator<T>::m_index >= m_tree->size()) {
      m_parent_stack.clear();
      return;
    } else if (m_parent_stack.is_empty()) {
      ConstNodeInfo root_info {m_tree->m_root, 0};
      m_parent_stack.push(root_info);
    }
    while (BaseIterator<T>::m_index < left_size() || BaseIterator<T>::m_index >= left_size() + node().size()) {
      m_parent_stack.pop();
    }
    assert(!m_parent_stack.is_empty());
    index_type current_index = left_size() + node().size(TREE_LEFT);
    while (current_index != BaseIterator<T>::m_index) {
      assert(BaseIterator<T>::m_index >= left_size() && BaseIterator<T>::m_index < left_size() + node().size());
      if (current_index > BaseIterator<T>::m_index) {
        assert(node().m_children[TREE_LEFT] != NULL);
        ConstNodeInfo info {node().m_children[TREE_LEFT], left_size()};
        m_parent_stack.push(info);
      } else {
        assert(current_index < BaseIterator<T>::m_index);
        assert(node().m_children[TREE_RIGHT] != NULL);
        ConstNodeInfo info {node().m_children[TREE_RIGHT], current_index + 1};
        m_parent_stack.push(info);
      }
      current_index = left_size() + node().size(TREE_LEFT);
    }
  }

}

#endif // DATASTRUCTURES_TREECONSTITERATOR_H
