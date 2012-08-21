#ifndef DATASTRUCTURES_FIBONACCIHEAP_H
#define DATASTRUCTURES_FIBONACCIHEAP_H

#include "DataStructures_global.h"
#include "fibonaccinode.h"
#include "arraylist.h"

namespace DataStructures {
  
  template <typename T>
  class FibonacciHeap
  {
  public:
    inline FibonacciHeap();

    inline FibonacciHeap(const FibonacciHeap& other);

    template <typename Iterator>
    inline FibonacciHeap(const Iterator& begin, const Iterator& end);

    inline void insert(const T& element);

    inline void remove(const T& element);

    inline const T& top() const;

    inline T& top();

    inline T pop();

    // Note that the other FibonacciHeap will be unusable.
    inline void merge(FibonacciHeap& other);

  private:
    typedef FibonacciNode<T>* NodePointer;

    ArrayList<NodePointer> m_children;

    index_type m_size;

    Treap<NodePointer> m_elements;

  };
  
} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCIHEAP_H
