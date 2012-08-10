#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "infiniterandom.h"
#include "treapiterator.h"

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

    inline T& get_element() const { return m_element; }

    inline index_type size() const { return m_size; }

    TreapIterator<T> iterator_at(ArrayList<TreapIterator<T>::NodeInfo>& parent_stack, index_type index);

  private:
    inline void insert(NodePointer &parent, const T& element, index_type direction);
    inline void rotate(NodePointer &parent, index_type direction);
    inline index_type left_size() const { return children[LEFT] == NULL ? 0 : children[LEFT]->size(); }
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
  TreapIterator<T> TreapNode<T>::iterator_at(ArrayList<TreapIterator<T>::NodeInfo>& parent_stack, index_type index)
  {
    assert(index < m_size);
    parent_stack.push(TreapIterator<T>::NodeInfo(this, this_index));
    index_type left_size = left_size();
    if (index == left_size) {
      return TreapIterator<T>(parent_stack, index);
    } else if (index < left_size) {
      return m_children[LEFT]->iterator_at(parent_stack, index);
    } else {
      return m_children[RIGHT]->iterator_at(parent_stack, index - left_size - 1);
    }
  }

  template <typename T>
  void TreapNode<T>::insert(NodePointer &parent, const T& element)
  {
    ++m_size;
    if (element < m_element) {
      insert(parent, element, LEFT);
    } else {
      insert(parent, element, RIGHT);
    }
  }

  template <typename T>
  inline T& TreapNode<T>::get_element() const
  {
    return element;
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
