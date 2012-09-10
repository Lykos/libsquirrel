#ifndef DATASTRUCTURES_FIBONACCINODE_H
#define DATASTRUCTURES_FIBONACCINODE_H

#include "stddef.h"

namespace DataStructures {

  template <typename T, typename Compare>
  class FibonacciHeap;
  
  template <typename T, typename Compare>
  class FibonacciNode
  {
    friend class FibonacciHeap<T, Compare>;

  public:
    typedef size_t size_type;

    const T& element() const;

    T& element();

  private:
    inline FibonacciNode(const FibonacciHeap<T, Compare>* heap, const T& m_element);

    FibonacciNode& operator=(const FibonacciNode& other) = delete;

    FibonacciNode& operator=(FibonacciNode&& other) = delete;

    FibonacciNode(const FibonacciNode& other) = delete;

    FibonacciNode(FibonacciNode&& other) = delete;

    const FibonacciHeap<T, Compare>* const m_heap;

    T m_element;

    FibonacciNode* m_parent = NULL;

    FibonacciNode* m_child = NULL;

    FibonacciNode* m_left;

    FibonacciNode* m_right;

    size_type m_children = 0;

    bool m_marked = false;

  };
  
} // namespace DataStructures

// This can be defined to solve some dependency cycles.
// But then fibonaccinode.hpp has to be included manually.
#ifndef DATASTRUCTURES_FIBNACCINODE_NO_HPP
#include "fibonaccinode.hpp"
#endif

#endif // DATASTRUCTURES_FIBONACCINODE_H
