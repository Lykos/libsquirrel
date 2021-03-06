#ifndef DATASTRUCTURES_TREAPNODE_HPP
#define DATASTRUCTURES_TREAPNODE_HPP

#include "treapnode.h"
#include "infiniterandom.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  TreapNode<T>::TreapNode(const T& new_element, TreapNode<T>* new_parent, direction new_parent_direction):
    TreeNode<T, TreapNode<T> >(new_element, new_parent, new_parent_direction),
    randomness ()
  {}

  template <typename T>
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert((!TreeNode<T, TreapNode<T> >::is_leaf()));
    if (TreeNode<T, TreapNode<T> >::m_children[TREE_LEFT] == nullptr) {
      return TREE_RIGHT;
    } else if (TreeNode<T, TreapNode<T> >::m_children[TREE_RIGHT] == nullptr) {
      return TREE_LEFT;
    } else {
      return TreeNode<T, TreapNode<T> >::m_children[TREE_LEFT]->m_randomness < TreeNode<T, TreapNode<T> >::m_children[TREE_RIGHT]->m_randomness ? TREE_LEFT : TREE_RIGHT;
    }
  }

}

#endif // DATASTRUCTURES_TREAPNODE_HPP
