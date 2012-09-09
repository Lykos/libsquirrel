#ifndef DATASTRUCTURES_FIBONACCINODE_HPP
#define DATASTRUCTURES_FIBONACCINODE_HPP

#include "fibonaccinode.h"

namespace DataStructures {
  
  template <typename T>
  FibonacciNode::FibonacciNode(const FibonacciHeap<T>* heap,
                               const T& element):
    m_heap (heap),
    m_element (element)
  {
    m_left = this;
    m_right = this;
  }

  template <typename T>
  const T& FibonacciNode::element() const
  {
    return m_element;
  }

  template <typename T>
  T& FibonacciNode::element()
  {
    return m_element;
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCINODE_HPP
