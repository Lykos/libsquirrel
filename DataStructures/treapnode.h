#ifndef DATASTRUCTURES_TREAPNODE_H
#define DATASTRUCTURES_TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"
#include <iostream>

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const TreapNode<T>& it);

  template <typename T>
  class TreapNode : public TreeNode<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const TreapNode<T>& it);
  public:
    typedef TreeConstIterator<T> const_iterator;

    typedef TreeIterator<T> iterator;

  private:
    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef TreapNode<T>* TreapNodePointer;

    typedef const TreapNode<T>* ConstTreapNodePointer;

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

    typedef typename TreeNode<T>::direction direction;

    inline direction min_rand_direction() const;

  public:
    inline TreapNode(const TreapNode& other);

    inline TreapNode(const T& element);

    inline NodePointer insert(const T& element);

  protected:
    inline direction remove_direction() const { return min_rand_direction(); }

    inline NodePointer new_node(const T& element) { return new TreapNode<T>(element); }

  private:
    inline ConstTreapNodePointer child(direction dir) const { return static_cast<const TreapNodePointer>(TreeNode<T>::m_children[dir]); }

    inline TreapNodePointer child(direction dir) { return static_cast<TreapNodePointer>(TreeNode<T>::m_children[dir]); }

    InfiniteRandom m_randomness;

  };

  template <typename T>
  inline TreapNode<T>::TreapNode(const TreapNode<T> &other):
    TreeNode<T>(other),
    m_randomness (other.m_randomness)
  {
  }

  template <typename T>
  TreapNode<T>::TreapNode(const T& element):
    TreeNode<T>(element),
    m_randomness ()
  {
  }

  template <typename T>
  inline typename TreapNode<T>::NodePointer TreapNode<T>::insert(const T& element)
  {
    direction dir = TreeNode<T>::element_direction(element);
    TreeNode<T>::insert(element);
    NodePointer result = this;
    assert(child(dir)->m_randomness.stuff());
    assert(m_randomness.stuff());
    if (child(dir)->m_randomness < m_randomness) {
      result = TreeNode<T>::rotate(dir);
    }
    assert_size();
    return result;
  }

  template <typename T>
  inline typename TreapNode<T>::direction TreapNode<T>::min_rand_direction() const
  {
    assert(TreeNode<T>::m_size > 1);
    assert(TreeNode<T>::m_children[TREE_LEFT] != NULL || TreeNode<T>::m_children[TREE_RIGHT] != NULL);
    if (TreeNode<T>::m_children[TREE_LEFT] == NULL) {
      return TREE_RIGHT;
    } else if (TreeNode<T>::m_children[TREE_RIGHT] == NULL) {
      return TREE_LEFT;
    } else {
      return child(TREE_LEFT)->m_randomness < child(TREE_RIGHT)->m_randomness ? TREE_LEFT : TREE_RIGHT;
    }
  }

}

#endif // DATASTRUCTURES_TREAPNODE_H
