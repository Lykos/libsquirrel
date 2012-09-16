#ifndef DATASTRUCTURES_TREAPNODE_H
#define DATASTRUCTURES_TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  struct TreapNode : public TreeNode<T, TreapNode<T> >
  {
    typedef typename TreeNode<T, TreapNode<T> >::direction direction;

    inline TreapNode(const T& new_element, TreapNode<T>* new_parent = nullptr, direction new_parent_direction = TREE_INVALID);

    InfiniteRandom randomness;

    inline direction min_rand_direction() const;

  };

}

#include "treapnode.hpp"

#endif // DATASTRUCTURES_TREAPNODE_H
