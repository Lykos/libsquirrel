#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "basetypes.h"
#include "treenode.h"
#include "stdexcept"

#define assert_balance(node_pointer) { assert(node_pointer->m_balance == -1 || node_pointer->m_balance == 0 || node_pointer->m_balance == 1); }

namespace DataStructures {

  template <typename T>
  struct AVLNode : public TreeNode<T, AVLNode<T> >
  {
    typedef char balance_t;

    typedef typename TreeNode<T, AVLNode<T> >::direction direction;

    inline AVLNode(const T& new_element, AVLNode<T>* new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    balance_t balance;

  };


  template <typename T>
  AVLNode<T>::AVLNode(const T& new_element, AVLNode<T>* new_parent, direction new_parent_direction):
    TreeNode<T, AVLNode<T> >(new_element, new_parent, new_parent_direction),
    balance (0)
  {
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLNODE_H
