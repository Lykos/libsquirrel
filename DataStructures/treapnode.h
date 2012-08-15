#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "infiniterandom.h"
#include "treenode.h"
#include <iostream>

#define LEFT 0
#define RIGHT 1
#define assert_size() assert(TreeNode<T>::m_size == TreeNode<T>::left_size() + 1 + TreeNode<T>::right_size())

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const TreapNode<T>& it);

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

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

    typedef typename TreeNode<T>::direction direction;

    inline direction min_rand_direction() const;

  public:
    TreapNode(const TreapNode& other);

    TreapNode(const T& element);

    NodePointer insert(const T& element);

    inline direction remove_direction() const { return min_rand_direction(); }

  private:

    inline const TreapNodePointer child(direction dir) const { return static_cast<const TreapNodePointer>(TreeNode<T>::m_children[dir]); }

    inline TreapNodePointer child(direction dir) { return static_cast<TreapNodePointer>(TreeNode<T>::m_children[dir]); }

    InfiniteRandom m_randomness;

  };

  template <typename T>
  TreapNode<T>::TreapNode(const TreapNode<T> &other):
    TreeNode<T>(other),
    m_randomness (other.m_randomness)
  {
  }

  template <typename T>
  TreapNode<T>::TreapNode(const T& element):
    TreeNode<T>(element)
  {
  }

  template <typename T>
  typename TreapNode<T>::NodePointer TreapNode<T>::insert(const T& element)
  {
    ++TreeNode<T>::m_size;
    direction dir = TreeNode<T>::element_direction(element);
    if (TreeNode<T>::m_children[dir] == NULL) {
      TreeNode<T>::m_children[dir] = new TreapNode<T>(element);
    } else {
      TreeNode<T>::m_children[dir] = child(dir)->insert(element);
    }
    NodePointer result = this;
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
    assert(TreeNode<T>::m_children[LEFT] != NULL || TreeNode<T>::m_children[RIGHT] != NULL);
    if (TreeNode<T>::m_children[LEFT] == NULL) {
      return RIGHT;
    } else if (TreeNode<T>::m_children[RIGHT] == NULL) {
      return LEFT;
    } else {
      return child(LEFT)->m_randomness < child(RIGHT)->m_randomness ? LEFT : RIGHT;
    }
  }

}

#undef LEFT
#undef RIGHT

#endif // TREAPNODE_H
