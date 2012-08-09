#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "infiniterandom.h"

namespace DataStructures {



  template <typename T>
  class TreapNode
  {
  public:
    typedef TreapNode<T>* NodePointer;

    TreapNode(const T& element);

    void insert(NodePointer &parent, const T& element);

    bool search(const T& element);

    T remove(const T& element);

  private:
    inline void insert(NodePointer &parent, const T& element, index_type direction);
    inline void rotate(NodePointer &parent, index_type direction);
    static const index_type LEFT = 0;
    static const index_type RIGHT = 1;
    index_type m_size;
    T m_element;
    InfiniteRandom m_randomness;
    ArrayList<NodePointer> m_children;
  };

  template <typename T>
  TreapNode<T>::TreapNode(const T& element):
    m_element (element),
    m_children (2, NULL)
  {
  }

  template <typename T>
  void TreapNode<T>::insert(NodePointer &parent, const T& element)
  {
    if (element < m_element) {
      insert(parent, element, LEFT);
    } else {
      insert(parent, element, RIGHT);
    }
  }

  inline void TreapNode<T>::insert(NodePointer &parent, const T& element, index_type direction)
  {
    if (m_children[direction] == NULL) {
      m_children[direction] = new TreapNode<T>(element);
    } else {
      m_children[direction]->insert(this, element);
    }
    if (m_children[direction]->m_randomness < m_randomness) {
      rotate(parent, direction);
    }
  }

  inline void TreapNode<T>::rotate(NodePointer &parent, index_type direction)
  {
    parent = m_children[direction];
    m_children[direction] = parent->m_children[1 - direction];
    parent->m_children[1 - direction] = this;
  }

}

#endif // TREAPNODE_H
