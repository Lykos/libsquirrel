#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "avlnode.h"
#include "basetree.h"
#include <ostream>

namespace DataStructures {

  typedef char balance_t;

  template <typename T>
  class AVLTree;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& it);

  template <typename T>
  class AVLTree : public BaseTree<T, AVLNode<T> >
  {
    friend std::ostream& operator<< <> (std::ostream& out, const AVLTree<T>& it);

  public:
    inline AVLTree();

    inline AVLTree(const AVLTree<T>& other);

    inline void insert(const T &element);

    inline bool remove(const T &element);

    template <typename Iterator>
    inline AVLTree(const Iterator& begin, const Iterator& end);

  private:
    typedef typename AVLNode<T>::balance_t balance_t;

    typedef typename BaseTree<T, AVLNode<T> >::direction direction;

    inline void rebalance(AVLNode<T>* current, direction dir);

    inline void inner_remove(AVLNode<T>* node);

    inline void exchange_content(AVLNode<T>* node1, AVLNode<T>* node2);

    inline void non_inner_remove_rebalance(AVLNode<T>* node);

  };
  
} // namespace DataStructures

#include "avltree.hpp"

#endif // DATASTRUCTURES_AVLTREE_H
