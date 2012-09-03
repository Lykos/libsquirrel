#ifndef DATASTRUCTURES_TREENODE_H
#define DATASTRUCTURES_TREENODE_H

#include "basetypes.h"
#include "infiniterandom.h"

namespace DataStructures {

  template <typename T, typename Node>
  struct TreeNode
  {
    typedef unsigned char direction;

    inline TreeNode(const T& new_element, Node* new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    inline direction element_direction(const T& other_element) const { return other_element < element ? TREE_LEFT : TREE_RIGHT; }

    inline direction min_size_direction() const { return dir_size(TREE_LEFT) < dir_size(TREE_RIGHT) ? TREE_LEFT : TREE_RIGHT; }

    inline index_type dir_size(direction dir) const { return children[dir] == NULL ? 0 : children[dir]->size; }

    inline bool is_inner() const { return children[TREE_LEFT] != NULL && children[TREE_RIGHT] != NULL; }

    inline bool is_leaf() const { return children[TREE_LEFT] == NULL && children[TREE_RIGHT] == NULL; }

    inline bool is_root() const { return parent == NULL; }

    inline virtual ~TreeNode() {}

    inline index_type calculated_size() const { return dir_size(TREE_LEFT) + 1 + dir_size(TREE_RIGHT); }

    T element;

    index_type size;

    Node* parent;

    direction parent_direction;

    Node* children[2] = {NULL, NULL};

  };

  template <typename T, typename Node>
  TreeNode<T, Node>::TreeNode(const T& new_element, Node* new_parent, direction new_parent_direction):
    element (new_element),
    size (1),
    parent (new_parent),
    parent_direction (new_parent_direction)
  {
  }

}

#endif // DATASTRUCTURES_TREENODE_H
