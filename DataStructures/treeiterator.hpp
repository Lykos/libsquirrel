#ifndef DATASTRUCTURES_TREEITERATOR_HPP
#define DATASTRUCTURES_TREEITERATOR_HPP

#include "treeiterator.h"
#include "baseiterator.h"
#include "treenode.h"
#include "conditiontype.h"
#include "preconditionviolation.h"

#define PREC_INDEX_TREE_IT(index) PREC(OutOfRange, index < BaseIt::m_container->size());

namespace DataStructures {

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>::operator TreeIterator<T const, Node const, Tree const>() const
  {
    return TreeIterator<T const, Node const, Tree const>(BaseIt::m_container, BaseIt::m_index, m_current, m_left_size);
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>::TreeIterator(Tree* tree, size_type index):
    BaseIt (tree, index),
    m_current (NULL),
    m_left_size (0)
  {
    local_search();
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>::TreeIterator(Tree *tree, size_type index, Node* current, size_type left_size):
    BaseIt (tree, index),
    m_current (current),
    m_left_size (left_size)
  {}

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> operator+(typename Node::difference_type index, const TreeIterator<T, Node, Tree>& other)
  {
    return other + index;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> TreeIterator<T, Node, Tree>::operator++(int)
  {
    TreeIterator<T, Node, Tree> old (*this);
    operator++();
    return old;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>& TreeIterator<T, Node, Tree>::operator++()
  {
    ++BaseIt::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> TreeIterator<T, Node, Tree>::operator--(int)
  {
    TreeIterator<T, Node, Tree> old (*this);
    operator--();
    return old;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>& TreeIterator<T, Node, Tree>::operator--()
  {
    --BaseIt::m_index;
    local_search();
    return *this;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> TreeIterator<T, Node, Tree>::operator+(difference_type index) const
  {
    TreeIterator<T, Node, Tree> other (*this);
    return other += index;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> TreeIterator<T, Node, Tree>::operator-(difference_type index) const
  {
    TreeIterator<T, Node, Tree> other (*this);
    return other -= index;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>& TreeIterator<T, Node, Tree>::operator+=(difference_type index)
  {
    BaseIt::m_index += index;
    local_search();
    return *this;
  }

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree>& TreeIterator<T, Node, Tree>::operator-=(difference_type index)
  {
    BaseIt::m_index -= index;
    local_search();
    return *this;
  }

  template <typename T, typename Node, typename Tree>
  inline T& TreeIterator<T, Node, Tree>::operator*() const
  {
    PREC_INDEX_TREE_IT(BaseIt::m_index);
    // Should only happen if the user does funny things while iterating
    PREC(InvalidIterator, m_current != NULL);
    return m_current->element;
  }

  template <typename T, typename Node, typename Tree>
  inline T& TreeIterator<T, Node, Tree>::operator[](difference_type index) const
  {
    PREC_INDEX_TREE_IT(BaseIt::m_index + index);
    return *(operator+(index));
  }

  template <typename T, typename Node, typename Tree>
  inline T* TreeIterator<T, Node, Tree>::operator->() const
  {
    return &operator*();
  }

  template <typename T, typename Node, typename Tree>
  inline void TreeIterator<T, Node, Tree>::local_search()
  {
    if (BaseIt::m_index >= BaseIt::m_container->size()) {
      m_current = NULL;
      return;
    } else if (m_current == NULL) {
      m_current = BaseIt::m_container->m_root;
      m_left_size = 0;
    }
    while (BaseIt::m_index < m_left_size || BaseIt::m_index >= m_left_size + m_current->size) {
      direction parent_dir = m_current->parent_direction;
      m_current = m_current->parent;
      if (parent_dir == TREE_RIGHT) {
        PREC(InvalidIterator, m_left_size >= m_current->dir_size(TREE_LEFT) + 1);
        m_left_size -= m_current->dir_size(TREE_LEFT) + 1;
      }
    }
    size_type current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    while (current_index != BaseIt::m_index) {
      PREC(InvalidIterator, m_current != NULL);
      PREC(InvalidIterator, (BaseIt::m_index >= m_left_size));
      PREC(InvalidIterator, (BaseIt::m_index < m_left_size + m_current->size));
      if (current_index > BaseIt::m_index) {
        PREC(InvalidIterator, m_current->children[TREE_LEFT] != NULL);
        m_current = m_current->children[TREE_LEFT];
      } else {
        PREC(InvalidIterator, (current_index < BaseIt::m_index));
        PREC(InvalidIterator, m_current->children[TREE_RIGHT] != NULL);
        m_left_size = current_index + 1;
        m_current = m_current->children[TREE_RIGHT];
      }
      current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    }
  }

}

#endif // DATASTRUCTURES_TREEITERATOR_HPP
