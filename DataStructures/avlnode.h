#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "treenode.h"

namespace DataStructures {

  template <typename T>
  struct AVLNode : public TreeNode<T, AVLNode<T> >
  {
    typedef char balance_t;

    typedef typename TreeNode<T, AVLNode<T> >::direction direction;

    inline AVLNode(const T& new_element, AVLNode<T>* new_parent = nullptr, direction new_parent_direction = TREE_INVALID);

    balance_t balance;

  };
  
} // namespace DataStructures

#include "avlnode.hpp"

#endif // DATASTRUCTURES_AVLNODE_H
