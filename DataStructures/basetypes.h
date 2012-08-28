#ifndef DATASTRUCTURES_BASETYPES_H
#define DATASTRUCTURES_BASETYPES_H

#include "DataStructures_global.h"

namespace DataStructures {

  typedef u_int64_t index_type;
  typedef int64_t difference_type;

  template <typename T>
  class BaseList;

  template <typename T, typename List>
  class ListIterator;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Queue;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Heap;

  template <typename T, typename Node>
  class BaseTree;

  template <typename T, typename Node, typename Tree>
  class TreeIterator;

  template <typename T, typename Tree>
  class TreeConstIterator;

  template <typename T, typename Node>
  class TreeNode;

  template <typename T>
  class TreapNode;

  template <typename T>
  class AVLNode;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT AVLTree;

  class DATASTRUCTURESSHARED_EXPORT LongInt;

  class DATASTRUCTURESSHARED_EXPORT UniformLongIntDistribution;

#define TREE_LEFT 0
#define TREE_RIGHT 1
#define TREE_INVALID 2

}

#endif // DATASTRUCTURES_BASETYPES_H
