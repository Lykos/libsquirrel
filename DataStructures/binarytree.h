#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <ostream>
#include "basetypes.h"
#include "DataStructures_global.h"
#include "basetree.h"
#include "treenode.h"

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT BinaryTree : public BaseTree<T, TreeNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const BinaryTree<T>& it);

  public:
    inline BinaryTree();

    inline BinaryTree(const BinaryTree<T>& other);

    template <typename Iterator>
    inline BinaryTree(const Iterator& begin, const Iterator& end);

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree)
  {
    out << "BinaryTree[";
    for (typename BinaryTree<T>::const_iterator it = tree.begin(); it < tree.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < tree.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  inline BinaryTree<T>::BinaryTree():
    BaseTree<T, TreeNode<T> >()
  {
  }

  template <typename T>
  inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& other):
    BaseTree<T, TreeNode<T> >(other)
  {
  }

  template <typename T>
  template <typename Iterator>
  inline BinaryTree<T>::BinaryTree(const Iterator& begin, const Iterator& end):
    BaseTree<T, TreeNode<T> > (begin, end)
  {
  }

}

#endif // BINARYTREE_H
