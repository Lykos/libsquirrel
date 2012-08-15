#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "DataStructures_global.h"
#include "avlnode.h"
#include "basetree.h"

namespace DataStructures {

  template<T>
  class AVLTree : public BaseTree<T, AVLNode>
  {
  public:
    AVLTree();
  };
  
}

#endif // DATASTRUCTURES_AVLTREE_H
