#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "basetypes.h"
#include "avlnode.h"
#include "basetree.h"
#include <ostream>

namespace DataStructures {

  typedef char balance_t;

  static const balance_t BALANCE_SIGN[] = {-1, 1};

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const AVLTree<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT AVLTree : public BaseTree<T, AVLNode<T> >
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

    typedef typename BaseTree<T, AVLNode<T> >::NodePointer NodePointer;

    typedef AVLNode<T>* AVLNodePointer;

    typedef typename BaseTree<T, AVLNode<T> >::direction direction;

    inline void rebalance(AVLNodePointer current, direction dir);

    inline void inner_remove(AVLNodePointer node);

    inline void exchange_content(AVLNodePointer node1, AVLNodePointer node2);

    inline void non_inner_remove_rebalance(AVLNodePointer node);

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
  template <typename Iterator>
  inline AVLTree<T>::AVLTree(const Iterator& begin, const Iterator& end):
    BaseTree<T, AVLNode<T> > (begin, end)
  {
  }

  template <typename T>
  inline bool AVLTree<T>::remove(const T &element)
  {
    AVLNodePointer current = BaseTree<T, AVLNode<T> >::root();
    while (current != NULL) {
      if (current->element == element) {
        if (current->is_inner()) {
          inner_remove(current);
        } else {
          non_inner_remove_rebalance(current);
        }
        return true;
      }
      direction dir = current->element_direction(element);
      current = current->child(dir);
    }
    return false;
  }

  template <typename T>
  inline void AVLTree<T>::inner_remove(AVLNodePointer node)
  {
    assert(node != NULL);
    AVLNodePointer current = node->child(TREE_LEFT);
    assert(current != NULL);
    while (current->children[TREE_RIGHT] != NULL) {
      current = current->child(TREE_RIGHT);
    }
    exchange_content(current, node);
    non_inner_remove_rebalance(current);
  }

  template <typename T>
  inline void AVLTree<T>::non_inner_remove_rebalance(AVLNodePointer node)
  {
    assert(node != NULL);
    assert(!(node->is_inner()));
    AVLNodePointer current = node->parent2();
    direction dir = node->parent_direction;
    BaseTree<T, AVLNode<T> >::non_inner_remove(node);
    balance_t old_balance = current->balance;
    current->balance -= BALANCE_SIGN[dir];
    balance_t new_balance = current->balance;
    dir = current->parent_direction;
    current = current->parent2();
    while (current != NULL && old_balance != new_balance && new_balance == 0) {
      old_balance = current->balance;
      if (old_balance == -BALANCE_SIGN[dir]) {
        rebalance(current, 1 - dir);
        return;
      }
      current->balance -= BALANCE_SIGN[dir];
      new_balance = current->balance;
      dir = current->parent_direction;
      current = current->parent2();
    }
  }

  template <typename T>
  inline void AVLTree<T>::exchange_content(AVLNodePointer node1, AVLNodePointer node2)
  {
    std::swap(node1->element, node2->element);
  }

  template <typename T>
  inline void AVLTree<T>::insert(const T& element)
  {
    if (BaseTree<T, AVLNode<T> >::m_root == NULL) {
      BaseTree<T, AVLNode<T> >::m_root = new AVLNode<T>(element);
      return;
    }
    AVLNodePointer new_node = BaseTree<T, AVLNode<T> >::internal_insert(element);
    direction dir = new_node->parent_direction;
    AVLNodePointer current = new_node->parent2();
    balance_t old_balance = current->balance;
    current->balance += BALANCE_SIGN[dir];
    balance_t new_balance = current->balance;
    dir = current->parent_direction;
    current = current->parent2();
    while (current != NULL && old_balance != new_balance && new_balance != 0) {
      old_balance = current->balance;
      if (old_balance == BALANCE_SIGN[dir]) {
        rebalance(current, dir);
        return;
      }
      current->balance += BALANCE_SIGN[dir];
      new_balance = current->balance;
      dir = current->parent_direction;
      current = current->parent2();
    }
  }

  template <typename T>
  inline void AVLTree<T>::rebalance(AVLNodePointer current, direction dir)
  {
    assert(current != NULL);
    assert(current->balance == BALANCE_SIGN[dir]);
    AVLNodePointer child = current->child(dir);
    assert(child != NULL);
    if (current->balance == child->balance) {
      // Normal rotate
      child->balance = 0;
      current->balance = 0;
      BaseTree<T, AVLNode<T> >::rotate(current, dir);
    } else {
      // Zic zac rotate
      assert(current->balance == -child->balance);
      AVLNodePointer new_parent = child->child(1 - dir);
      if (new_parent->balance == BALANCE_SIGN[dir]) {
        current->balance = -BALANCE_SIGN[dir];
        child->balance = 0;
      } else if (new_parent->balance == -BALANCE_SIGN[dir]) {
        current->balance = 0;
        child->balance = BALANCE_SIGN[dir];
      } else {
        assert(new_parent->balance == 0);
        current->balance = 0;
        child->balance = 0;
      }
      new_parent->balance = 0;
      BaseTree<T, AVLNode<T> >::rotate(child, 1 - dir);
      BaseTree<T, AVLNode<T> >::rotate(current, dir);
    }
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLTREE_H
