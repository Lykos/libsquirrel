#ifndef DATASTRUCTURES_TREEITERATOR_H
#define DATASTRUCTURES_TREEITERATOR_H

#include "baseiterator.h"
#include "treenode.h"

#define PREC_INDEX_TREE_IT(index) PREC(OutOfRange, index < BaseIt::m_container->size());

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

    inline T& operator*() const;

    inline T& operator[](difference_type i) const;

    inline T* operator->() const;

    inline operator TreeIterator<T const, Node const, Tree const>() const;

  private:
    typedef BaseIterator<T, Tree, TreeIterator<T, Node, Tree> > BaseIt; // Shortcut for terribly complicated type

    typedef typename Tree::direction direction;

    Node* m_current;

    size_type m_left_size;

    inline void local_search();

  };

}

#include "treeiterator.hpp"

#endif // DATASTRUCTURES_TREEITERATOR_H
