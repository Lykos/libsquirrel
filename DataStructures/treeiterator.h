#ifndef DATASTRUCTURES_TREEITERATOR_H
#define DATASTRUCTURES_TREEITERATOR_H

#include "baseiterator.h"
#include "treenode.h"

#ifndef NDEBUG
#include <sstream>
#define tree_iterator_check_index(index) if (index >= m_tree->size()) { std::ostringstream oss; oss << "Invalid index " << index << " for BaseTree of size " << m_tree->size() << "."; throw typename Tree::range_error(oss.str()); }
#else
#define tree_iterator_check_index(index)
#endif

namespace DataStructures {

  template <typename T, typename Tree>
  TreeIterator<T, Tree> operator+(index_type i, const TreeIterator<T, Tree>& it);

  template <typename T, typename Tree>
  class TreeIterator : public BaseIterator<T>
  {
    friend TreeIterator<T, Tree> operator+ <> (index_type i, const TreeIterator<T, Tree>& it);
    friend class TreeConstIterator<T, Tree>;
  public:
    typedef struct { TreeNode<T> *node; index_type left_size; } NodeInfo;
    TreeIterator(Tree* tree, index_type index = 0);
    TreeIterator(const TreeIterator<T, Tree>& other);
    difference_type operator-(const TreeIterator<T, Tree>& other) const;
    difference_type operator-(const TreeConstIterator<T, Tree>& other) const;
    TreeIterator<T, Tree> operator++(int);
    TreeIterator<T, Tree>& operator++();
    TreeIterator<T, Tree> operator--(int);
    TreeIterator<T, Tree>& operator--();
    TreeIterator<T, Tree>& operator=(const TreeIterator<T, Tree>& other);
    TreeIterator<T, Tree> operator+(index_type i) const;
    TreeIterator<T, Tree> operator-(index_type i) const;
    TreeIterator<T, Tree>& operator+=(index_type i);
    TreeIterator<T, Tree>& operator-=(index_type i);
    T& operator*();
    T& operator[](index_type i);
  private:
    Tree* m_tree;
    ArrayList<NodeInfo> m_parent_stack;
    inline void local_search();
    inline TreeNode<T>& node() const { return *m_parent_stack.back().node; }
    inline index_type left_size() const { return m_parent_stack.back().left_size; }
  };

  template <typename T, typename Tree>
  TreeIterator<T, Tree>::TreeIterator(Tree* tree, index_type index):
    BaseIterator<T> (index),
    m_tree (tree),
    m_parent_stack (0)
  {
    local_search();
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>::TreeIterator(const TreeIterator<T, Tree>& other):
    BaseIterator<T> (other.m_index),
    m_tree (other.m_tree),
    m_parent_stack (other.m_parent_stack)
  {
  }

  template <typename T, typename Tree>
  difference_type TreeIterator<T, Tree>::operator-(const TreeIterator<T, Tree>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Tree>
  difference_type TreeIterator<T, Tree>::operator-(const TreeConstIterator<T, Tree>& other) const
  {
    return BaseIterator<T>::m_index - other.m_index;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree> operator+(index_type index, const TreeIterator<T, Tree>& other)
  {
    return other + index;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree> TreeIterator<T, Tree>::operator++(int)
  {
    TreeIterator<T, Tree> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree> TreeIterator<T, Tree>::operator--(int)
  {
    TreeIterator<T, Tree> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator=(const TreeIterator& other)
  {
    BaseIterator<T>::m_index = other.m_index;
    m_parent_stack = other.m_parent_stack;
    return *this;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree> TreeIterator<T, Tree>::operator+(index_type index) const
  {
    TreeIterator<T, Tree> other (*this);
    return other += index;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree> TreeIterator<T, Tree>::operator-(index_type index) const
  {
    TreeIterator<T, Tree> other (*this);
    return other -= index;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  T& TreeIterator<T, Tree>::operator*()
  {
    tree_iterator_check_index(BaseIterator<T>::m_index);
    return m_parent_stack.back().node->get_element();
  }

  template <typename T, typename Tree>
  T& TreeIterator<T, Tree>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T, typename Tree>
  inline void TreeIterator<T, Tree>::local_search()
  {
    if (BaseIterator<T>::m_index >= m_tree->size()) {
      m_parent_stack.clear();
      return;
    } else if (m_parent_stack.is_empty()) {
      NodeInfo root_info {m_tree->m_root, 0};
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
        NodeInfo info {node().m_children[TREE_LEFT], left_size()};
        m_parent_stack.push(info);
      } else {
        assert(current_index < BaseIterator<T>::m_index);
        assert(node().m_children[TREE_RIGHT] != NULL);
        NodeInfo info {node().m_children[TREE_RIGHT], current_index + 1};
        m_parent_stack.push(info);
      }
      current_index = left_size() + node().size(TREE_LEFT);
    }
  }

}

#endif // DATASTRUCTURES_TREEITERATOR_H
