#ifndef DATASTRUCTURES_BASETREE_H
#define DATASTRUCTURES_BASETREE_H

#include "treeiterator.h"
#include <ostream>

namespace DataStructures {

  template <typename T, typename Node, typename Compare>
  class BaseTree;

  template <typename T, typename Node, typename Compare>
  std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node, Compare>& it);

  template <typename T, typename Node, typename Compare>
  class BaseTree
  {
    friend std::ostream& operator<< <> (std::ostream& out, const BaseTree<T, Node, Compare>& it);

    friend class TreeIterator<T, Node, BaseTree<T, Node, Compare> >;

    friend class TreeIterator<T const, Node const, BaseTree<T, Node, Compare> const >;

  public:
    typedef TreeIterator<T const, Node const, BaseTree<T, Node, Compare> const> const_iterator;

    typedef TreeIterator<T, Node, BaseTree<T, Node, Compare> > iterator;

  protected:
    typedef typename Node::direction direction;

  public:
    typedef typename Node::size_type size_type;

    typedef typename Node::difference_type difference_type;

    inline BaseTree(const Compare& compare);

    inline BaseTree(const BaseTree<T, Node, Compare>& other);

    template <typename InputIterator>
    inline BaseTree(InputIterator begin, InputIterator end, const Compare& compare);

    inline virtual ~BaseTree();

    inline BaseTree& operator=(const BaseTree<T, Node, Compare>& other);

    inline bool operator==(const BaseTree<T, Node, Compare>& other) const;

    inline bool operator!=(const BaseTree<T, Node, Compare>& other) const;

    inline void clear();

    inline void merge(const BaseTree<T, Node, Compare>& other);

    inline virtual void insert(const T& element);

    template <typename InputIterator>
    inline void insert_all(InputIterator begin, InputIterator end);

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

    Compare m_compare;

    inline direction element_direction(Node* current, const T& element) const;

    inline void rotate(Node* node, direction dir);

    inline Node* internal_insert(const T& element);

    inline void non_inner_remove(Node* node);

  };

}

#include "basetree.hpp"

#endif // DATASTRUCTURES_BASETREE_H
