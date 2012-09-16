#ifndef DATASTRUCTURES_FIBONACCIHEAP_HPP
#define DATASTRUCTURES_FIBONACCIHEAP_HPP

#include "fibonacciheap.h"
#include "fibonaccinode.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include "arithmetichelper.h"
#include <cstring>

namespace DataStructures {

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>::FibonacciHeap(const Compare& compare):
    m_compare (compare)
  {}

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>::FibonacciHeap(std::initializer_list<T> list):
    FibonacciHeap<T, Compare>(list.begin(), list.end())
  {}

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>::FibonacciHeap(const FibonacciHeap<T, Compare>& other):
    m_root (nullptr),
    m_size (other.m_size),
    m_compare (other.m_compare)
  {
    merge(other);
  }

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>::FibonacciHeap(FibonacciHeap<T, Compare>&& other):
    m_root (other.m_root),
    m_size (other.m_size),
    m_compare (std::move(other.m_compare))
  {
    other.m_root = nullptr;
    other.m_size = 0;
  }

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>::~FibonacciHeap()
  {
    traverse([](node_pointer node) { delete node; });
  }

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>& FibonacciHeap<T, Compare>::operator=(const FibonacciHeap<T, Compare>& other)
  {
    ~FibonacciHeap();
    m_root = nullptr;
    m_size = 0;
    m_compare = other.m_compare;
    merge(other);
  }

  template <typename T, typename Compare>
  inline FibonacciHeap<T, Compare>& FibonacciHeap<T, Compare>::operator=(FibonacciHeap<T, Compare>&& other)
  {
    m_root = other.m_root;
    m_size = other.m_size;
    m_compare = std::move(other.m_compare);
    other.m_root = nullptr;
    other.m_size = 0;
  }

  template <typename T, typename Compare>
  template <typename InputIterator>
  inline FibonacciHeap<T, Compare>::FibonacciHeap(InputIterator begin, InputIterator end, const Compare& compare):
    m_compare (compare)
  {
    for (; begin != end; ++begin) {
      push(*begin);
    }
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::decrease_key(node_pointer node, const T& element)
  {
    PREC(InvalidNode, node != nullptr);
    PREC(InvalidNode, node->m_heap == this);
    PREC(NotDecreased, element > node->element());
    node->element() = element;
    decrease_key(node);
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::decrease_key(node_pointer node)
  {
    PREC(InvalidNode, node != nullptr);
    PREC(InvalidNode, node->m_heap == this);
    if (node == m_root) {
      return;
    }
    node_pointer parent = node->m_parent;
    if (parent != nullptr && m_compare(node->element(), parent->element())) {
      take_out(node);
      mark(parent);
      push(node);
    }
    if (m_compare(node->element(), m_root->element())) {
      m_root = node;
    }
  }

  template <typename T, typename Compare>
  inline typename FibonacciHeap<T, Compare>::node_pointer FibonacciHeap<T, Compare>::push(const T& element)
  {
    ++m_size;
    node_pointer node = new FibonacciNode<T, Compare>(this, element);
    push(node);
    return node;
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::remove(node_pointer node)
  {
    PREC(InvalidNode, node != nullptr);
    PREC(InvalidNode, node->m_heap == this);
    if (node != m_root) {
      assert(m_root != nullptr);
      // Behaves like decreasing the key to -infty
      take_out(node);
      if (node->m_parent != nullptr) {
        mark(node->m_parent);
      }
      push(node);
      m_root = node;
    }
    pop();
  }

  template <typename T, typename Compare>
  inline const T& FibonacciHeap<T, Compare>::top() const
  {
    return m_root->element();
  }

  template <typename T, typename Compare>
  inline T& FibonacciHeap<T, Compare>::top()
  {
    PREC(EmptyList, m_size > 0);
    return m_root->element();
  }

  template <typename T, typename Compare>
  inline T FibonacciHeap<T, Compare>::pop()
  {
    PREC(EmptyList, m_size > 0);
    assert(m_root != nullptr);
    T min = m_root->element();
    --m_size;
    // TODO Make sure this really suffices
    size_type max_deg = 2 * ArithmeticHelper::log2(m_size);
    node_pointer *nodes = new node_pointer[max_deg + 1];
    memset(nodes, 0, sizeof(node_pointer) * (max_deg + 1));
    if (m_root->m_child != nullptr) {
      node_pointer node = m_root->m_child;
      do {
        cleanup_insert(nodes, node, max_deg);
        node = node->m_left;
      } while (node != m_root->m_child);
    }
    node_pointer node = m_root->m_left;
    while (node != m_root) {
      node_pointer left = node->m_left;
      cleanup_insert(nodes, node, max_deg);
      node = left;
    }
    delete m_root;
    m_root = nullptr;
    for (size_type i = 0; i <= max_deg; ++i) {
      if (nodes[i] != nullptr) {
        push(nodes[i]);
      }
    }
    delete[] nodes;
    return min;
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::merge(const FibonacciHeap& other)
  {
    other.traverse([this](node_pointer node) { push(new FibonacciNode<T, Compare>(this, node->element())); });
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::merge(FibonacciHeap&& other)
  {
    PREC(SelfMerge, this != &other);
    if (other.m_root == nullptr) {
      return;
    } else if (m_root == nullptr) {
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

  template <typename T, typename Compare>
  inline typename FibonacciHeap<T, Compare>::size_type FibonacciHeap<T, Compare>::size() const
  {
    return m_size;
  }

  template <typename T, typename Compare>
  inline bool FibonacciHeap<T, Compare>::empty() const
  {
    return m_size == 0;
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::push(node_pointer node)
  {
    assert(node != nullptr);
    if (m_root == nullptr) {
      m_root = node;
      connect_self(node);
    } else {
      add_left(m_root, node);
      if (m_compare(node->element(), m_root->element())) {
        m_root = node;
      }
    }
    node->m_parent = nullptr;
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::take_out(node_pointer node)
  {
    assert(node != nullptr);
    assert(node != m_root);
    node_pointer left = node->m_left;
    node->m_right->m_left = left;
    left->m_right = node->m_right;
    node_pointer parent = node->m_parent;
    if (parent != nullptr) {
      assert(parent->m_children > 0);
      --(parent->m_children);
      if (parent->m_child == node) {
        if (parent->m_children == 0) {
          assert(node->m_left == node);
          assert(node->m_right == node);
          parent->m_child = nullptr;
        } else {
          assert(node->m_left != node);
          assert(node->m_right != node);
          parent->m_child = node->m_left;
          for (node_pointer child = node->m_left->m_left; child != node; child = child->m_left) {
            if (m_compare(child->element(), parent->m_child->element())) {
              parent->m_child = child;
            }
          }
        }
      } else {
        assert(parent->m_child != nullptr);
        assert(parent->m_children > 0);
        assert(node->m_left != node);
        assert(node->m_right != node);
      }
    }
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::mark(node_pointer node)
  {
    while (node != nullptr && node->m_parent != nullptr && node->m_marked) {
      node_pointer parent = node->m_parent;
      take_out(node);
      push(node);
      node = parent;
    }
    if (node != nullptr && node->m_parent != nullptr) {
      node->m_marked = true;
    }
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::cleanup_insert(node_pointer *nodes, node_pointer node, size_type max_deg)
  {
    assert(node != nullptr);
    assert(node->m_children <= max_deg);
    while (nodes[node->m_children] != nullptr) {
      node_pointer other = nodes[node->m_children];
      assert(node->m_children == other->m_children);
#ifndef NDEBUG
      size_type old_children = node->m_children;
#endif
      nodes[node->m_children] = nullptr;
      if (m_compare(other->element(), node->element())) {
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


  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::add_child(node_pointer node, node_pointer new_child)
  {
    assert(node != nullptr);
    assert(new_child != nullptr);
    new_child->m_parent = node;
    ++(node->m_children);
    node_pointer child = node->m_child;
    if (child == nullptr) {
      connect_self(new_child);
      node->m_child = new_child;
    } else {
      add_left(child, new_child);
      if (m_compare(new_child->element(), child->element())) {
        node->m_child = new_child;
      }
    }
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::add_left(node_pointer node, node_pointer new_left)
  {
    new_left->m_left = node->m_left;
    new_left->m_right = node;
    node->m_left->m_right = new_left;
    node->m_left = new_left;
  }


  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::connect_self(node_pointer node)
  {
    node->m_left = node;
    node->m_right = node;
  }

  template <typename T, typename Compare>
  inline void FibonacciHeap<T, Compare>::traverse(void (*operation)(node_pointer node)) const
  {
    // Note that this has to handle the case that operation deletes the pointer
    if (m_root != nullptr) {
      ArrayList<node_pointer> terminator_stack;
      ArrayList<node_pointer> current_stack;
      node_pointer current = m_root;
      assert(current->m_left->m_right == current);
      // Ensure termination in this level
      terminator_stack.push_back(current);
      // But still enter the round
      bool nodes_left = true;
      bool children_done = false;
      while (!terminator_stack.empty()) {
        if (!nodes_left && current == terminator_stack.back()) {
          // Go back one level
          terminator_stack.pop_back();
          if (terminator_stack.empty()) {
            break;
          }
          // Restore current pointer from the previous level.
          current = current_stack.pop_back();
          children_done = true;
          nodes_left = true;
        } else if (!children_done && current->m_child != nullptr) {
          // Save current position from this level
          current_stack.push_back(current);
          current = current->m_child;
          // Ensure termination in this level
          terminator_stack.push_back(current);
          nodes_left = true;
        } else {
          // There may or may not be a node left, but this only triggers
          // termination if current == terminator
          nodes_left = false;
          assert(current->m_left->m_right == current);
          current = current->m_left;
          operation(current->m_right);
        }
      }
    }
  }

} // namespace DataStructures

#endif // DATASTRUCTURES_FIBONACCIHEAP_HPP
