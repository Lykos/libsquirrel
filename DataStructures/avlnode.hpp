#ifndef DATASTRUCTURES_AVLNODE_HPP
#define DATASTRUCTURES_AVLNODE_HPP

#include "avlnode.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  AVLNode<T>::AVLNode(const T& new_element, AVLNode<T>* new_parent, direction new_parent_direction):
    TreeNode<T, AVLNode<T> >(new_element, new_parent, new_parent_direction),
    balance (0)
  {
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLNODE_HPP
