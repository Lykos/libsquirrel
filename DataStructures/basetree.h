#ifndef DATASTRUCTURES_BASETREE_H
#define DATASTRUCTURES_BASETREE_H

#include "treeiterator.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Node>
  class BaseTree;

  template <typename T, typename Node>
  std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node>& it);

  template <typename T, typename Node>
  class BaseTree
  {
    friend std::ostream& operator<< <> (std::ostream& out, const BaseTree<T, Node>& it);

    friend class TreeIterator<T, Node, BaseTree<T, Node> >;

    friend class TreeIterator<T const, Node const, BaseTree<T, Node> const >;

  public:
    typedef TreeIterator<T const, Node const, BaseTree<T, Node> const> const_iterator;

    typedef TreeIterator<T, Node, BaseTree<T, Node> > iterator;

  protected:
    typedef typename Node::direction direction;

  public:
    typedef typename Node::size_type size_type;

    typedef typename Node::difference_type difference_type;

    inline BaseTree();

    inline BaseTree(const BaseTree<T, Node>& other);

    template <typename Iterator>
    inline BaseTree(Iterator begin, Iterator end);

    inline virtual ~BaseTree();

    inline BaseTree& operator=(const BaseTree<T, Node>& other);

    inline bool operator==(const BaseTree<T, Node>& other) const;

    inline bool operator!=(const BaseTree<T, Node>& other) const;

    inline void clear();

    inline void merge(const BaseTree<T, Node>& other);

    inline virtual void insert(const T& element);

    template <typename Iterator>
    inline void insert_all(const Iterator& begin, const Iterator& end);

    inline bool search(const T& element) const;

    inline iterator lower_bound(const T& element);

    inline iterator upper_bound(const T& element);

    inline std::pair< iterator, iterator > equal_range(const T& element);

    inline T& operator[](size_type index);

    inline const_iterator lower_bound(const T& element) const;

    inline const_iterator upper_bound(const T& element) const;

    inline std::pair< const_iterator, const_iterator > equal_range(const T& element) const;

    inline const T& operator[](size_type index) const;

    inline bool remove(const T& element);

    inline size_type remove_all(const T& element);

    inline size_type size() const;

    inline bool is_empty() const;

    inline iterator begin();

    inline iterator end();

    inline const_iterator begin() const;

    inline const_iterator end() const;

  protected:
    Node* m_root;

    inline void rotate(Node* node, direction dir);

    inline Node* internal_insert(const T& element);

    inline void non_inner_remove(Node* node);

  };

}

#include "basetree.hpp"

#endif // DATASTRUCTURES_BASETREE_H
