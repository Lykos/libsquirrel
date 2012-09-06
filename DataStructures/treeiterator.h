#ifndef DATASTRUCTURES_TREEITERATOR_H
#define DATASTRUCTURES_TREEITERATOR_H

#include "baseiterator.h"
#include "treenode.h"

#ifndef NDEBUG
#include <sstream>
#define tree_iterator_check_index(index) if (index >= BaseIt::m_container->size()) { std::ostringstream oss; oss << "Invalid index " << index << " for BaseTree of size " << BaseIt::m_container->size() << "."; throw typename Tree::range_error(oss.str()); }
#else
#define tree_iterator_check_index(index)
#endif

namespace DataStructures {

  template <typename T, typename Node, typename Tree>
  class TreeIterator;

  template <typename T, typename Node, typename Tree>
  inline TreeIterator<T, Node, Tree> operator+(typename Node::difference_type i, const TreeIterator<T, Node, Tree>& it);

  template <typename T, typename Node, typename Tree>
  class TreeIterator : public BaseIterator<T, Tree, TreeIterator<T, Node, Tree> >
  {
    friend TreeIterator<T, Node, Tree> operator+ <> (typename Node::difference_type i, const TreeIterator<T, Node, Tree>& it);

  public:
    typedef typename Node::size_type size_type;

    typedef typename Node::difference_type difference_type;

    inline explicit TreeIterator(Tree* tree, size_type index = 0);

    inline TreeIterator(Tree *tree, size_type index, Node* current, size_type left_size);

    inline TreeIterator<T, Node, Tree> operator++(int);

    inline TreeIterator<T, Node, Tree>& operator++();

    inline TreeIterator<T, Node, Tree> operator--(int);

    inline TreeIterator<T, Node, Tree>& operator--();

    inline TreeIterator<T, Node, Tree> operator+(difference_type i) const;

    inline TreeIterator<T, Node, Tree> operator-(difference_type i) const;

    inline TreeIterator<T, Node, Tree>& operator+=(difference_type i);

    inline TreeIterator<T, Node, Tree>& operator-=(difference_type i);

    inline T& operator*();

    inline T& operator[](difference_type i);

    inline operator TreeIterator<T const, Node const, Tree const>() const;

  private:
    typedef BaseIterator<T, Tree, TreeIterator<T, Node, Tree> > BaseIt; // Shortcut for terribly complicated type

    typedef typename Tree::direction direction;

    Node* m_current;

    size_type m_left_size;

    inline void local_search();

  };

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
  inline T& TreeIterator<T, Node, Tree>::operator*()
  {
    assert(m_current != NULL);
    return m_current->element;
  }

  template <typename T, typename Node, typename Tree>
  inline T& TreeIterator<T, Node, Tree>::operator[](difference_type index)
  {
    return *(operator+(index));
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
        assert(m_left_size >= m_current->dir_size(TREE_LEFT) + 1);
        m_left_size -= m_current->dir_size(TREE_LEFT) + 1;
      }
    }
    size_type current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    while (current_index != BaseIt::m_index) {
      assert(m_current != NULL);
      assert((BaseIt::m_index >= m_left_size));
      assert((BaseIt::m_index < m_left_size + m_current->size));
      if (current_index > BaseIt::m_index) {
        assert(m_current->children[TREE_LEFT] != NULL);
        m_current = m_current->children[TREE_LEFT];
      } else {
        assert((current_index < BaseIt::m_index));
        assert(m_current->children[TREE_RIGHT] != NULL);
        m_left_size = current_index + 1;
        m_current = m_current->children[TREE_RIGHT];
      }
      current_index = m_left_size + m_current->dir_size(TREE_LEFT);
    }
  }

}

#endif // DATASTRUCTURES_TREEITERATOR_H
