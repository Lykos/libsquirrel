#ifndef DATASTRUCTURES_AVLNODE_H
#define DATASTRUCTURES_AVLNODE_H

#include "basetypes.h"
#include "treenode.h"
#include "stdexcept"

#define assert_balance(node_pointer) { ConstAVLNodePointer node = static_cast<ConstAVLNodePointer>(node_pointer); assert(node->m_balance == -1 || node->m_balance == 0 || node->m_balance == 1); }

namespace DataStructures {

  typedef char balance_t;

  static const balance_t BALANCE_SIGN[] = {-1, 1};

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const AVLNode<T>& it);

  template <typename T>
  class AVLNode : public TreeNode<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const AVLNode<T>& it);

    typedef char balance_t;

  private:
    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef AVLNode<T>* AVLNodePointer;

    typedef const AVLNode<T>* ConstAVLNodePointer;

    typedef typename TreeNode<T>::direction direction;

    inline direction min_balance_direction() const;

  public:
    inline AVLNode(const AVLNode& other);

    inline AVLNode(const T& element);

    inline NodePointer insert(const T& element);

  protected:
    inline direction remove_direction() const { throw std::logic_error("Not implemented."); }

    inline NodePointer new_node(const T& element) { return new AVLNode<T>(element); }

  private:
    inline NodePointer update_balance(balance_t old_child_balance, direction dir);

    inline NodePointer rebalance(direction dir);

    inline NodePointer normal_rotate(direction dir);

    inline NodePointer zic_zac_rotate(direction dir);

    inline ConstAVLNodePointer child(direction dir) const { return static_cast<const AVLNodePointer>(TreeNode<T>::m_children[dir]); }

    inline AVLNodePointer child(direction dir) { return static_cast<AVLNodePointer>(TreeNode<T>::m_children[dir]); }

    balance_t m_balance;

  };


  template <typename T>
  AVLNode<T>::AVLNode(const AVLNode<T> &other):
    TreeNode<T>(other),
    m_balance (other.m_balance)
  {
  }

  template <typename T>
  AVLNode<T>::AVLNode(const T& element):
    TreeNode<T>(element),
    m_balance (0)
  {
  }

  template <typename T>
  typename AVLNode<T>::NodePointer AVLNode<T>::insert(const T& element)
  {
    ++TreeNode<T>::m_size;
    direction dir = TreeNode<T>::element_direction(element);
    if (child(dir) == NULL) {
      TreeNode<T>::m_children[dir] = new AVLNode<T>(element);
      m_balance += BALANCE_SIGN[dir];
      assert_balance(this);
      return this;
    } else {
      balance_t old_child_balance = child(dir)->m_balance;
      TreeNode<T>::m_children[dir] = child(dir)->insert(element);
      return update_balance(old_child_balance, dir);
    }
  }

  template <typename T>
  inline typename AVLNode<T>::NodePointer AVLNode<T>::update_balance(balance_t old_child_balance, direction dir)
  {
    if (old_child_balance != 0 || old_child_balance == child(dir)->m_balance) {
      assert_balance(this);
      return this;
    }
    // If the balance changes from 0 to something else, then the balance of this node changes.
    m_balance += BALANCE_SIGN[dir];
    if (m_balance <= 1 && m_balance >= -1) {
      assert_balance(this);
      return this;
    } else {
      return rebalance(dir);
    }
  }

  template <typename T>
  inline typename AVLNode<T>::NodePointer AVLNode<T>::rebalance(direction dir)
  {
    if (BALANCE_SIGN[dir] == child(dir)->m_balance) {
      return normal_rotate(dir);
    } else {
      return zic_zac_rotate(dir);
    }
  }

  template <typename T>
  inline typename AVLNode<T>::NodePointer AVLNode<T>::normal_rotate(direction dir)
  {
    child(dir)->m_balance = 0;
    m_balance = 0;
    NodePointer new_root = TreeNode<T>::rotate(dir);
    assert_balance(this);
    assert_balance(new_root);
    return new_root;
  }

  template <typename T>
  inline typename AVLNode<T>::NodePointer AVLNode<T>::zic_zac_rotate(direction dir)
  {
    AVLNodePointer dir_child = child(dir);
    // Note that dir_child->child(1 - dir) is guaranteed to exist in the case for
    // which this method can be called
    balance_t lower_balance = dir_child->child(1 - dir)->m_balance;
    if (lower_balance == BALANCE_SIGN[dir]) {
      m_balance = 0;
      dir_child->m_balance = 1;
    } else if (lower_balance == BALANCE_SIGN[1 - dir]) {
      m_balance = -1;
      dir_child->m_balance = 0;
    } else {
      assert(lower_balance == 0);
      m_balance = 0;
      dir_child->m_balance = 0;
    }
    TreeNode<T>::m_children[dir] = dir_child->rotate(1 - dir);
    NodePointer new_root = TreeNode<T>::rotate(dir);
    assert_balance(this);
    assert_balance(new_root);
    assert_balance(dir_child);
    return new_root;
  }

  template <typename T>
  inline typename AVLNode<T>::direction AVLNode<T>::min_balance_direction() const
  {
    assert(TreeNode<T>::m_size > 1);
    assert(TreeNode<T>::m_children[TREE_LEFT] != NULL || TreeNode<T>::m_children[TREE_RIGHT] != NULL);
    if (TreeNode<T>::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T>::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return child(TREE_LEFT)->m_balance < child(TREE_RIGHT)->m_balance ? TREE_LEFT : TREE_RIGHT;
    }
  }
  
} // namespace DataStructures

#endif // DATASTRUCTURES_AVLNODE_H
