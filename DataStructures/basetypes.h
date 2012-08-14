#ifndef BASETYPES_H
#define BASETYPES_H

#include "DataStructures_global.h"

namespace DataStructures {

  typedef unsigned long long int index_type;
  typedef long long int difference_type;

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

  template <typename T, typename Node>
  class TreeIterator;

  template <typename T, typename Node>
  class TreeConstIterator;

  template <typename T>
  class TreeNode;

  template <typename T>
  class TreapNode;

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap;

}

#endif // BASETYPES_H
