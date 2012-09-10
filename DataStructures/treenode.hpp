#ifndef DATASTRUCTURES_TREENODE_HPP
#define DATASTRUCTURES_TREENODE_HPP

#include "treenode.h"
#include "infiniterandom.h"
#include <cstddef>

namespace DataStructures {

  template <typename T, typename Node>
  inline typename TreeNode<T, Node>::direction TreeNode<T, Node>::min_size_direction() const
  {
    return dir_size(TREE_LEFT) < dir_size(TREE_RIGHT) ? TREE_LEFT : TREE_RIGHT;
  }

  template <typename T, typename Node>
  inline typename TreeNode<T, Node>::size_type TreeNode<T, Node>::dir_size(direction dir) const
  {
    return children[dir] == NULL ? 0 : children[dir]->size;
  }

  template <typename T, typename Node>
  inline bool TreeNode<T, Node>::is_inner() const
  {
    return children[TREE_LEFT] != NULL && children[TREE_RIGHT] != NULL;
  }

  template <typename T, typename Node>
  inline bool TreeNode<T, Node>::is_leaf() const
  {
    return children[TREE_LEFT] == NULL && children[TREE_RIGHT] == NULL;
  }

  template <typename T, typename Node>
  inline bool TreeNode<T, Node>::is_root() const
  {
    return parent == NULL;
  }

  template <typename T, typename Node>
  inline TreeNode<T, Node>::~TreeNode()
  {}

  template <typename T, typename Node>
  inline typename TreeNode<T, Node>::size_type TreeNode<T, Node>::calculated_size() const
  {
    return dir_size(TREE_LEFT) + 1 + dir_size(TREE_RIGHT);
  }

  template <typename T, typename Node>
  TreeNode<T, Node>::TreeNode(const T& new_element, Node* new_parent, direction new_parent_direction):
    element (new_element),
    size (1),
    parent (new_parent),
    parent_direction (new_parent_direction)
  {
  }

}

#endif // DATASTRUCTURES_TREENODE_HPP
