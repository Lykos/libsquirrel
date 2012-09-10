#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "avlnode.h"
#include "basetree.h"
#include "less.h"
#include <ostream>
#include <initializer_list>

namespace DataStructures {

  typedef char balance_t;

  template <typename T, typename Compare>
  class AVLTree;

  template <typename T, typename Compare>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T, Compare>& it);

  template <typename T, typename Compare = Less<T> >
  class AVLTree : public BaseTree<T, AVLNode<T>, Compare>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const AVLTree<T, Compare>& it);

  public:
    inline explicit AVLTree(const Compare& compare = Compare());

    inline AVLTree(std::initializer_list<T> list);

    inline void insert(const T &element);

    inline bool remove(const T &element);

    template <typename InputIterator>
    inline AVLTree(InputIterator begin, InputIterator end, const Compare& compare = Compare());

  private:
    typedef typename AVLNode<T>::balance_t balance_t;

    typedef typename BaseTree<T, AVLNode<T>, Compare>::direction direction;

    inline void rebalance(AVLNode<T>* current, direction dir);

    inline void inner_remove(AVLNode<T>* node);

    inline void exchange_content(AVLNode<T>* node1, AVLNode<T>* node2);

    inline void non_inner_remove_rebalance(AVLNode<T>* node);

  };
  
} // namespace DataStructures

#include "avltree.hpp"

#endif // DATASTRUCTURES_AVLTREE_H
