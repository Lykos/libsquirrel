#ifndef DATASTRUCTURES_FIBONACCIHEAP_HPP
#define DATASTRUCTURES_FIBONACCIHEAP_HPP

#include "fibonacciheap.h"
#include "fibonaccinode.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include "arithmetichelper.h"

namespace DataStructures {

  template <typename T>
  inline FibonacciHeap<T>::FibonacciHeap()
  {}

  template <typename T>
  inline FibonacciHeap<T>::FibonacciHeap(const FibonacciHeap<T>& other):
    m_root (NULL),
    m_size (other.m_size)
  {
    merge(other);
  }

  inline FibonacciHeap<T>::FibonacciHeap(FibonacciHeap<T>&& other):
    m_root (other.m_root),
    m_size (other.m_size)
  {
    other.m_root = NULL;
    other.m_size = 0;
  }

  inline FibonacciHeap<T>::~FibonacciHeap()
  {
    traverse([](node_pointer node) { delete node; });
  }

  inline FibonacciHeap& FibonacciHeap<T>::operator=(const FibonacciHeap<T>& other)
  {
    ~FibonacciHeap();
    m_root = NULL;
    m_size = 0;
    merge(other);
  }

  inline FibonacciHeap& FibonacciHeap<T>::operator=(FibonacciHeap<T>&& other):
    m_root (other.m_root),
    m_size (other.m_size)
  {
    other.m_root = NULL;
    other.m_size = 0;
  }

  template <typename Iterator>
  inline FibonacciHeap<T>::FibonacciHeap(Iterator begin, Iterator end)
  {
    for (; begin != end; ++begin) {
      push(*begin);
    }
  }

  template <typename T>
  inline void FibonacciHeap<T>::decrease_key(node_pointer node)
  {
    PREC(InvalidNode, node == NULL);
    PREC(InvalidNode, node->m_heap == this);
    if (node == m_root) {
      return;
    }
    node_pointer parent = node->m_parent;
    if (parent != NULL && node->element() < parent->element()) {
      take_out(node);
      mark(parent);
      push(node);
    }
    if (node->element() < m_root->element()) {
      m_root = node;
    }
  }

  template <typename T>
  inline typename FibonacciHeap<T>::node_pointer FibonacciHeap<T>::push(const T& element)
  {
    ++m_size;
    node_pointer node = new node_pointer(element);
    push(node);
    return node;
  }

  template <typename T>
  inline void FibonacciHeap<T>::remove(node_pointer node)
  {
    PREC(InvalidNode, node == NULL);
    PREC(InvalidNode, node->m_heap == this);
    if (node != m_root) {
      assert(m_root != NULL);
      // Behaves like decreasing the key to -infty
      take_out(node);
      if (node->m_parent != NULL) {
        mark(node->m_parent);
      }
      push(node);
      m_root = node;
    }
    pop();
  }

  template <typename T>
  inline const T& FibonacciHeap<T>::top() const
  {
    return m_root->element();
  }

  template <typename T>
  inline T& FibonacciHeap<T>::top()
  {
    return m_root->element();
  }

  template <typename T>
  inline T FibonacciHeap<T>::pop()
  {
    PREC(EmptyList, m_size > 0);
    assert(m_root != NULL);
    T min = m_root->element();
    --m_size;
    // TODO Make sure this really suffices
    size_type max_deg = 2 * ArithmeticHelper::log2(m_size);
    node_pointer *nodes = new node_pointer[max_deg + 1];
    if (m_root->m_child != NULL) {
      node_pointer node = m_root->m_child;
      do {
        cleanup_insert(nodes, node, max_deg);
        node = node->left;
      } while (node != m_root->m_child);
    }
    for (node_pointer node = m_root->left; node != m_root; node = node->m_left) {
      cleanup_insert(nodes, node, max_deg);
    }
    delete m_root;
    m_root = NULL;
    for (size_type i = 0; i < max_deg; ++i) {
      if (nodes[i] != NULL) {
        push(nodes[i]);
      }
    }
    return min;
  }

  template <typename T>
  inline void FibonacciHeap<T>::merge(const FibonacciHeap& other)
  {
    other.traverse([](node_pointer node) { push(new FibonacciNode<T>(node->element())); });
  }

  template <typename T>
  inline void FibonacciHeap<T>::merge(FibonacciHeap&& other)
  {
    PREC(SelfMerge, this != &other);
    if (other.m_root == NULL) {
      return;
    } else if (m_root == NULL) {
      m_root = other.m_root;
      return;
    }
    node_pointer left = m_root->m_left;
    m_root->m_left = other.m_root;
    node_pointer right = other.m_root->right;
    other.m_root->m_right = m_root;
    right->m_left = left;
    left->m_right = right;
  }

  template <typename T>
  inline void FibonacciHeap<T>::push(node_pointer node)
  {
    assert(node != NULL);
    if (m_root == NULL) {
      m_root = node;
      connect_self(node);
    } else {
      add_left(m_root, node);
      if (node->element < m_root->element()) {
        m_root = node;
      }
    }
    node->m_parent = NULL;
  }

  template <typename T>
  inline void FibonacciHeap<T>::take_out(node_pointer node)
  {
    assert(node != NULL);
    assert(node != m_root);
    node_pointer left = node->m_left;
    node->m_right->m_left = left;
    left->m_right = node->m_right;
    node_pointer parent = node->m_parent;
    if (parent != NULL) {
      assert(parent->m_children > 0);
      --(parent->m_children);
      if (parent->m_child == node) {
        if (parent->m_children == 0) {
          assert(node->m_left == node);
          assert(node->m_right == node);
          parent->m_child = NULL;
        } else {
          assert(node->m_left != node);
          assert(node->m_right != node);
          parent->m_child = node->m_left;
          for (node_pointer child = node->m_left->m_left; child != node; child = child->m_left) {
            if (child < parent->m_child) {
              parent->m_child = child;
            }
          }
        }
      } else {
        assert(parent->m_child != NULL);
        assert(parent->m_children > 0);
        assert(node->m_left != node);
        assert(node->m_right != node);
      }
    }
  }

  template <typename T>
  inline void FibonacciHeap<T>::mark(node_pointer node)
  {
    while (node != NULL && node->m_parent != NULL && node->m_marked) {
      node_pointer parent = node->m_parent;
      take_out(node);
      push(node);
      node = parent;
    }
    if (node != NULL && node->m_parent != NULL) {
      node->m_marked = true;
    }
  }

  template <typename T>
  inline void FibonacciHeap<T>::cleanup_insert(node_pointer *nodes, node_pointer node, size_type max_deg)
  {
    assert(node != NULL);
    assert(node->m_children <= max_deg);
    while (nodes[node->m_children] != NULL) {
#ifndef NDEBUG
      size_type old_children = node->m_children;
#endif
      node_pointer other = nodes[node->m_children];
      if (other->element() < node->element()) {
        add_child(other, node);
        node = other;
      } else {
        add_child(node, other);
      }
      assert(node->m_children == old_children + 1);
      assert(node->m_children <= max_deg);
    }
    nodes[node->m_children] = node;
  }


  template <typename T>
  inline void FibonacciHeap<T>::add_child(node_pointer node, node_pointer new_child)
  {
    assert(node != NULL);
    assert(new_child != NULL);
    new_child->m_parent = node;
    ++(node->m_children);
    node_pointer child = node->m_child;
    if (child == NULL) {
      connect_self(new_child);
      node->m_child = new_child;
    } else {
      add_left(child, new_child);
      if (new_child->element() < child->element()) {
        node->m_child = new_child;
      }
    }
  }

  template <typename T>
  inline void FibonacciHeap<T>::add_left(node_pointer node, node_pointer new_left)
  {
    new_left->m_left = node->m_left;
    new_left->m_right = node;
    node->m_left->m_right = new_left;
    node->m_left = new_left;
  }


  template <typename T>
  inline void FibonacciHeap<T>::connect_self(node_pointer node)
  {
    node->m_left = node;
    node->m_right = node;
  }

  template <typename T>
  inline void FibonacciHeap<T>::traverse(void (*operation)(node_pointer node))
  {
    // Note that this has to handle the case that operation deletes the pointer
    if (m_root != NULL) {
      ArrayList<node_pointer> node_stack;
      node_pointer current = m_root;
      assert(current->m_left->m_right == current);
      // Ensure termination in this level
      node_stack.push_back(current);
      // But still enter the round
      bool first = true;
      while (!node_stack.empty()) {
        if (!first && current == node_stack.back()) {
          node_stack.pop_back();
          current = node_stack.back();
          // We have to do it here since we don't know the value of "first" of that level.
          current = current->m_left;
          operation(current->m_right);
        } else if (current->m_child != NULL) {
          current = current->m_child;
          // Ensure termination in this level
          node_stack.push_back(current);
          // But still enter the round
          first = true;
        } else {
          first = false;
          assert(current->m_left->m_right == current);
          current = current->m_left;
          operation(current->m_right);
        }
      }
    }
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCIHEAP_HPP
