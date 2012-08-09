#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "infiniterandom.h"

namespace DataStructures {

  template <typename T>
  class TreapNode
  {
  public:
    TreapNode(const T& element);

  private:
    T m_element;
    InfiniteRandom m_randomness;
    TreapNode<T> *left;
    TreapNode<T> *right;
  };

}

TreapNode::TreapNode(const T& element):
  m_element (element),
  left (NULL),
  right (NULL)
{
}

#endif // TREAPNODE_H
