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
  inline TreeIterator<T, Tree> operator+(index_type i, const TreeIterator<T, Tree>& it);

  template <typename T, typename Tree>
  class TreeIterator : public BaseIterator<T>
  {
    friend TreeIterator<T, Tree> operator+ <> (index_type i, const TreeIterator<T, Tree>& it);

    friend class TreeConstIterator<T, Tree>;

  public:
    inline TreeIterator(const Tree* tree, index_type index = 0);

    inline TreeIterator(const TreeIterator<T, Tree>& other);

    inline TreeIterator(TreeIterator<T, Tree>&& other);

    inline difference_type operator-(const TreeIterator<T, Tree>& other) const { return BaseIterator<T>::m_index - other.m_index; }

    inline difference_type operator-(const TreeConstIterator<T, Tree>& other) const { return BaseIterator<T>::m_index - other.m_index; }

    inline TreeIterator<T, Tree> operator++(int);

    inline TreeIterator<T, Tree>& operator++();

    inline TreeIterator<T, Tree> operator--(int);

    inline TreeIterator<T, Tree>& operator--();

    inline TreeIterator<T, Tree>& operator=(TreeIterator<T, Tree>&& other);

    inline TreeIterator<T, Tree>& operator=(const TreeIterator<T, Tree>& other);

    inline TreeIterator<T, Tree> operator+(index_type i) const;

    inline TreeIterator<T, Tree> operator-(index_type i) const;

    inline TreeIterator<T, Tree>& operator+=(index_type i);

    inline TreeIterator<T, Tree>& operator-=(index_type i);

    inline T& operator*();

    inline T& operator[](index_type i);

  private:
    const Tree* m_tree;

    typedef TreeNode<T>* NodePointer;

    typedef typename Tree::direction direction;

    NodePointer m_current;

    index_type m_left_size;

    inline void local_search();

  };

  template <typename T, typename Tree>
  TreeIterator<T, Tree>::TreeIterator(const Tree* tree, index_type index):
    BaseIterator<T> (index),
    m_tree (tree),
    m_current (NULL),
    m_left_size (0)
  {
    local_search();
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>::TreeIterator(TreeIterator<T, Tree>&& other):
    BaseIterator<T> (other.m_index),
    m_tree (other.m_tree),
    m_current (other.m_current),
    m_left_size (other.m_left_size)
  {
  }

  template <typename T, typename Tree>
  TreeIterator<T, Tree>::TreeIterator(const TreeIterator<T, Tree>& other):
    BaseIterator<T> (other.m_index),
    m_tree (other.m_tree),
    m_current (other.m_current),
    m_left_size (other.m_left_size)
  {
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree> operator+(index_type index, const TreeIterator<T, Tree>& other)
  {
    return other + index;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree> TreeIterator<T, Tree>::operator++(int)
  {
    TreeIterator<T, Tree> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator++()
  {
    ++BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree> TreeIterator<T, Tree>::operator--(int)
  {
    TreeIterator<T, Tree> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator--()
  {
    --BaseIterator<T>::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator=(TreeIterator&& other)
  {
    if (this == &other) {
      return *this;
    }
    BaseIterator<T>::operator=(other);
    m_tree = other.m_tree;
    m_current = other.m_current;
    m_left_size = other.m_left_size;
    return *this;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator=(const TreeIterator& other)
  {
    if (this == &other) {
      return *this;
    }
    BaseIterator<T>::operator=(other);
    m_tree = other.m_tree;
    m_current = other.m_current;
    m_left_size = other.m_left_size;
    return *this;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree> TreeIterator<T, Tree>::operator+(index_type index) const
  {
    TreeIterator<T, Tree> other (*this);
    return other += index;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree> TreeIterator<T, Tree>::operator-(index_type index) const
  {
    TreeIterator<T, Tree> other (*this);
    return other -= index;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator+=(index_type index)
  {
    BaseIterator<T>::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  inline TreeIterator<T, Tree>& TreeIterator<T, Tree>::operator-=(index_type index)
  {
    BaseIterator<T>::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Tree>
  inline T& TreeIterator<T, Tree>::operator*()
  {
    assert(m_current != NULL);
    return m_current->element;
  }

  template <typename T, typename Tree>
  inline T& TreeIterator<T, Tree>::operator[](index_type index)
  {
    return *(operator+(index));
  }

  template <typename T, typename Tree>
  inline void TreeIterator<T, Tree>::local_search()
  {
    if (BaseIterator<T>::m_index >= m_tree->size()) {
      m_current = NULL;
      return;
    } else if (m_current == NULL) {
      m_current = m_tree->m_root;
      m_left_size = 0;
    }
    while (BaseIterator<T>::m_index < m_left_size || BaseIterator<T>::m_index >= m_left_size + m_current->size) {
      direction parent_dir = m_current->parent_direction;
      m_current = m_current->parent;
      if (parent_dir == TREE_RIGHT) {
        assert(m_left_size >= m_current->dir_size(TREE_LEFT) + 1);
        m_left_size -= m_current->dir_size(TREE_LEFT) + 1;
      }
    }
    index_type current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    while (current_index != BaseIterator<T>::m_index) {
      assert(m_current != NULL);
      assert(BaseIterator<T>::m_index >= m_left_size);
      assert(BaseIterator<T>::m_index < m_left_size + m_current->size);
      if (current_index > BaseIterator<T>::m_index) {
        assert(m_current->children[TREE_LEFT] != NULL);
        m_current = m_current->children[TREE_LEFT];
      } else {
        assert(current_index < BaseIterator<T>::m_index);
        assert(m_current->children[TREE_RIGHT] != NULL);
        m_left_size = current_index + 1;
        m_current = m_current->children[TREE_RIGHT];
      }
      current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    }
  }

}

#endif // DATASTRUCTURES_TREEITERATOR_H
