#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "basetypes.h"
#include "avlnode.h"
#include "basetree.h"

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT AVLTree : public BaseTree<T, AVLNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const AVLTree<T>& it);

  public:
    inline AVLTree();

    inline AVLTree(const AVLTree<T>& other);

    template <typename Begin, typename End>
    inline AVLTree(Begin begin, End end);

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& tree)
  {
    out << "AVLTree[";
    for (typename AVLTree<T>::const_iterator it = tree.begin(); it < tree.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < tree.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  inline AVLTree<T>::AVLTree():
    BaseTree<T, AVLNode<T> >()
  {
  }

  template <typename T>
  inline AVLTree<T>::AVLTree(const AVLTree<T>& other):
    BaseTree<T, AVLNode<T> >(other)
  {
  }

  template <typename T>
  template <typename Begin, typename End>
  inline AVLTree<T>::AVLTree(Begin begin, End end):
    BaseTree<T, AVLNode<T> > (begin, end)
  {
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLTREE_H
