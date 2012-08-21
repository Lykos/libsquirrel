#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "basetypes.h"
#include "treenode.h"
#include "stdexcept"

#define assert_balance(node_pointer) { assert(node_pointer->m_balance == -1 || node_pointer->m_balance == 0 || node_pointer->m_balance == 1); }

namespace DataStructures {

  template <typename T>
  struct AVLNode : public TreeNode<T>
  {
    typedef char balance_t;

    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef AVLNode<T>* AVLNodePointer;

    typedef typename TreeNode<T>::direction direction;

    inline AVLNode(const T& new_element, NodePointer new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    balance_t balance;

    inline AVLNodePointer child(direction dir) { return static_cast<AVLNodePointer>(TreeNode<T>::children[dir]); }

    inline AVLNodePointer parent2() { return static_cast<AVLNodePointer>(TreeNode<T>::parent); }

  };


  template <typename T>
  AVLNode<T>::AVLNode(const T& new_element, NodePointer new_parent, direction new_parent_direction):
    TreeNode<T>(new_element, new_parent, new_parent_direction),
    balance (0)
  {
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLNODE_H
