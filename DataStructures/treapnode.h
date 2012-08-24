#ifndef DATASTRUCTURES_TREAPNODE_H
#define DATASTRUCTURES_TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  struct TreapNode : public TreeNode<T>
  {
    typedef TreapNode<T>* TreapNodePointer;

    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef typename TreeNode<T>::direction direction;

    inline TreapNode(const T& new_element, NodePointer new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    InfiniteRandom randomness;

    inline TreapNodePointer child(direction dir) { return static_cast<TreapNodePointer>(TreeNode<T>::children[dir]); }

    inline direction min_rand_direction() const;

    inline TreapNodePointer parent2() { return static_cast<TreapNodePointer>(TreeNode<T>::parent); }

  };

  template <typename T>
  TreapNode<T>::TreapNode(const T& new_element, NodePointer new_parent, direction new_parent_direction):
    TreeNode<T>(new_element, new_parent, new_parent_direction),
    randomness ()
  {
  }

  template <typename T>
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert(TreeNode<T>::m_size > 1);
    assert(TreeNode<T>::m_children[TREE_LEFT] != NULL || TreeNode<T>::m_children[TREE_RIGHT] != NULL);
    if (TreeNode<T>::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T>::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return child(TREE_LEFT)->m_randomness < child(TREE_RIGHT)->m_randomness ? TREE_LEFT : TREE_RIGHT;
    }
  }

}

#endif // DATASTRUCTURES_TREAPNODE_H
