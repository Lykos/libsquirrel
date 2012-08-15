#ifndef BASETYPES_H
#define BASETYPES_H

#include "DataStructures_global.h"

namespace DataStructures {

  typedef u_int64_t index_type;
  typedef int64_t difference_type;

  template <typename T>
  class BaseList;

  template <typename T, typename List>
  class ListIterator;

  template <typename T, typename List>
  class ListConstIterator;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Queue;

  template <typename T, typename Node>
  class BaseTree;

  template <typename T>
  class TreeIterator;

  template <typename T>
  class TreeConstIterator;

  template <typename T>
  class TreeNode;

  template <typename T>
  class TreapNode;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap;

}

#endif // BASETYPES_H
