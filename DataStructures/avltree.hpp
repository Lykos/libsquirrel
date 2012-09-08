#ifndef DATASTRUCTURES_AVLTREE_HPP
#define DATASTRUCTURES_AVLTREE_HPP

#include "avltree.h"
#include "avlnode.h"
#include "basetree.h"
#include <ostream>

namespace DataStructures {

  static const balance_t BALANCE_SIGN[] = {-1, 1};

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
    AVLNode<T>* current = BaseTree<T, AVLNode<T> >::m_root;
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
      current = current->children[dir];
    }
    return false;
  }

  template <typename T>
  inline void AVLTree<T>::inner_remove(AVLNode<T>* node)
  {
    assert(node != NULL);
    AVLNode<T>* current = node->children[TREE_LEFT];
    assert(current != NULL);
    while (current->children[TREE_RIGHT] != NULL) {
      current = current->children[TREE_RIGHT];
    }
    exchange_content(current, node);
    non_inner_remove_rebalance(current);
  }

  template <typename T>
  inline void AVLTree<T>::non_inner_remove_rebalance(AVLNode<T>* node)
  {
    assert(node != NULL);
    assert(!(node->is_inner()));
    AVLNode<T>* current = node->parent;
    direction dir = node->parent_direction;
    BaseTree<T, AVLNode<T> >::non_inner_remove(node);
    balance_t old_balance = current->balance;
    current->balance -= BALANCE_SIGN[dir];
    balance_t new_balance = current->balance;
    dir = current->parent_direction;
    current = current->parent;
    while (current != NULL && old_balance != new_balance && new_balance == 0) {
      old_balance = current->balance;
      if (old_balance == -BALANCE_SIGN[dir]) {
        rebalance(current, 1 - dir);
        return;
      }
      current->balance -= BALANCE_SIGN[dir];
      new_balance = current->balance;
      dir = current->parent_direction;
      current = current->parent;
    }
  }

  template <typename T>
  inline void AVLTree<T>::exchange_content(AVLNode<T>* node1, AVLNode<T>* node2)
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
    AVLNode<T>* new_node = BaseTree<T, AVLNode<T> >::internal_insert(element);
    direction dir = new_node->parent_direction;
    AVLNode<T>* current = new_node->parent;
    balance_t old_balance = current->balance;
    current->balance += BALANCE_SIGN[dir];
    balance_t new_balance = current->balance;
    dir = current->parent_direction;
    current = current->parent;
    while (current != NULL && old_balance != new_balance && new_balance != 0) {
      old_balance = current->balance;
      if (old_balance == BALANCE_SIGN[dir]) {
        rebalance(current, dir);
        return;
      }
      current->balance += BALANCE_SIGN[dir];
      new_balance = current->balance;
      dir = current->parent_direction;
      current = current->parent;
    }
  }

  template <typename T>
  inline void AVLTree<T>::rebalance(AVLNode<T>* current, direction dir)
  {
    assert(current != NULL);
    assert(current->balance == BALANCE_SIGN[dir]);
    AVLNode<T>* child = current->children[dir];
    assert(child != NULL);
    if (current->balance == child->balance) {
      // Normal rotate
      child->balance = 0;
      current->balance = 0;
      BaseTree<T, AVLNode<T> >::rotate(current, dir);
    } else {
      // Zic zac rotate
      assert(current->balance == -child->balance);
      AVLNode<T>* new_parent = child->children[1 - dir];
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

#endif // DATASTRUCTURES_AVLTREE_HPP
