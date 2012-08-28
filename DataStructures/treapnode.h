#ifndef DATASTRUCTURES_TREAPNODE_H
#define DATASTRUCTURES_TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  struct TreapNode : public TreeNode<T, TreapNode<T> >
  {
    typedef TreapNode<T>* TreapNodePointer;

    typedef typename TreeNode<T, TreapNode<T> >::direction direction;

    inline TreapNode(const T& new_element, TreapNode<T>* new_parent = NULL, direction new_parent_direction = TREE_INVALID);

    InfiniteRandom randomness;

    inline direction min_rand_direction() const;

  };

  template <typename T>
  TreapNode<T>::TreapNode(const T& new_element, TreapNode<T>* new_parent, direction new_parent_direction):
    TreeNode<T, TreapNode<T> >(new_element, new_parent, new_parent_direction),
    randomness ()
  {
  }

  template <typename T>
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert((!TreeNode<T, TreapNode<T> >::is_leaf()));
    if (TreeNode<T, TreapNode<T> >::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T, TreapNode<T> >::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return TreeNode<T, TreapNode<T> >::m_children[TREE_LEFT]->m_randomness < TreeNode<T, TreapNode<T> >::m_children[TREE_RIGHT]->m_randomness ? TREE_LEFT : TREE_RIGHT;
    }
  }

}

#endif // DATASTRUCTURES_TREAPNODE_H
