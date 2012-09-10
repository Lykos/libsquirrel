#ifndef DATASTRUCTURES_FIBONACCIHEAP_H
#define DATASTRUCTURES_FIBONACCIHEAP_H

#define DATASTRUCTURES_FIBONACCINODE_NO_HPP
#include "fibonaccinode.h"
// fibonaccinode.hpp is included at file end
#include "arraylist.h"

namespace DataStructures {
  
  template <typename T>
  class FibonacciHeap
  {
  public:
    typedef FibonacciNode<T>* node_pointer;

    typedef typename Node<T>::size_type size_type;

    inline FibonacciHeap();

    inline FibonacciHeap(const FibonacciHeap& other);

    inline FibonacciHeap(FibonacciHeap&& other);

    inline ~FibonacciHeap();

    inline FibonacciHeap& operator=(const FibonacciHeap& other);

    inline FibonacciHeap& operator=(FibonacciHeap&& other);

    template <typename Iterator>
    inline FibonacciHeap(Iterator begin, Iterator end);

    inline void decrease_key(node_pointer node);

    inline node_pointer push(const T& element);

    inline void remove(const T& element);

    inline const T& top() const;

    inline T& top();

    inline T pop();

    inline void merge(const FibonacciHeap& other);

    inline void merge(FibonacciHeap&& other);

  private:
    node_pointer m_root = NULL;

    size_type m_size = 0;

    inline void push(node_pointer node);

    inline void take_out(node_pointer node);

    inline void mark(node_pointer node);

    inline void cleanup_insert(node_pointer *nodes, node_pointer node, size_type max_deg);

    inline void add_child(node_pointer node, node_pointer new_child);

    inline void add_left(node_pointer node, node_pointer new_left);

    inline void connect_self(node_pointer node);

    inline void traverse(void (*operation)(node_pointer node));

  };
  
} // namespace DataStructures

#include "fibonacciheap.hpp"
#include "fibonaccinode.hpp"

#endif // DATASTRUCTURES_FIBONACCIHEAP_H
