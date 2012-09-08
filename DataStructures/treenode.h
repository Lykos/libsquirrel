#ifndef DATASTRUCTURES_TREENODE_H
#define DATASTRUCTURES_TREENODE_H

#include "infiniterandom.h"
#include <cstddef>

#define TREE_LEFT 0
#define TREE_RIGHT 1
#define TREE_INVALID 2

namespace DataStructures {

  template <typename T, typename Node>
  struct TreeNode
  {
    typedef uint_fast8_t direction;

    typedef size_t size_type;

    typedef ptrdiff_t difference_type;

    inline TreeNode(const T& new_element, Node* new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    inline direction element_direction(const T& other_element) const;

    inline direction min_size_direction() const;

    inline size_type dir_size(direction dir) const;

    inline bool is_inner() const;

    inline bool is_leaf() const;

    inline bool is_root() const;

    inline virtual ~TreeNode();

    inline size_type calculated_size() const;

    T element;

    size_type size;

    Node* parent;

    direction parent_direction;

    Node* children[2] = {NULL, NULL};

  };

}

#include "treenode.hpp"

#endif // DATASTRUCTURES_TREENODE_H
