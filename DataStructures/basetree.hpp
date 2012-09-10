#ifndef DATASTRUCTURES_BASETREE_HPP
#define DATASTRUCTURES_BASETREE_HPP

#include "basetree.h"
#include "treeiterator.h"

#define PREC_INDEX_TREE(index) PREC(OutOfRange, (index < BaseTree<T, Node, Compare>::size()))
#define assert_size(node) \
  assert(node->size == node->calculated_size())
#define assert_parent(node) \
  assert(node == NULL || node->parent == NULL || node->parent->children[node->parent_direction] == node)
#define assert_child(node, dir) \
  assert(node == NULL || node->children[dir] == NULL || (node->children[dir]->parent == node && node->children[dir]->parent_direction == dir))
#define assert_children(node) \
  assert_child(node, TREE_LEFT); \
  assert_child(node, TREE_RIGHT)
#define assert_pointers(node) \
  assert_parent(node); \
  assert_children(node)

namespace DataStructures {

  template <typename T, typename Node, typename Compare>
  inline std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node, Compare>& tree)
  {
    out << "BaseTree[";
    for (typename BaseTree<T, Node, Compare>::const_iterator it = tree.begin(); it < tree.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < tree.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T, typename Node, typename Compare>
  inline bool BaseTree<T, Node, Compare>::operator!=(const BaseTree<T, Node, Compare>& other) const
  {
    return !operator==(other);
  }

  template <typename T, typename Node, typename Compare>
  inline bool BaseTree<T, Node, Compare>::search(const T& element) const
  {
    Node* current = m_root;
    while (current != NULL) {
      if (current->element == element) {
        return true;
      }
      direction dir = element_direction(current, element);
      current = current->children[dir];
    }
    return false;
  }

  template <typename T, typename Node, typename Compare>
  inline void BaseTree<T, Node, Compare>::merge(const BaseTree<T, Node, Compare>& other)
  {
    insert_all(other.begin(), other.end());
  }

  template <typename T, typename Node, typename Compare>
  inline void BaseTree<T, Node, Compare>::insert(const T& element)
  {
    internal_insert(element);
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::direction
  BaseTree<T, Node, Compare>::element_direction(Node* current, const T& element) const
  {
    return m_compare(element, current->element) ? TREE_LEFT : TREE_RIGHT;
  }

  template <typename T, typename Node, typename Compare>
  inline const T& BaseTree<T, Node, Compare>::operator[](size_type index) const
  {
    PREC_INDEX_TREE(index);
    Node* current = m_root;
    while (true) {
      assert(current != NULL);
      assert(index < current->size);
      size_type left = current->dir_size(TREE_LEFT);
      if (index < left) {
        current = current->children[TREE_LEFT];
      } else if (index > left) {
        index -= left + 1;
        current = current->children[TREE_RIGHT];
      } else {
        return current->element;
      }
    }
  }

  template <typename T, typename Node, typename Compare>
  inline T& BaseTree<T, Node, Compare>::operator[](size_type index)
  {
    PREC_INDEX_TREE(index);
    Node* current = m_root;
    while (true) {
      assert(current != NULL);
      assert(index < current->size);
      size_type left = current->dir_size(TREE_LEFT);
      if (index < left) {
        current = current->children[TREE_LEFT];
      } else if (index > left) {
        index -= left + 1;
        current = current->children[TREE_RIGHT];
      } else {
        return current->element;
      }
    }
  }

  template <typename T, typename Node, typename Compare>
  inline BaseTree<T, Node, Compare>::BaseTree(const Compare& compare):
    m_root (NULL),
    m_compare (compare)
  {}

  template <typename T, typename Node, typename Compare>
  inline BaseTree<T, Node, Compare>::BaseTree(const BaseTree<T, Node, Compare>& other):
    m_root (NULL),
    m_compare (other.m_compare)
  {
    insert_all(other.begin(), other.end());
  }

  template <typename T, typename Node, typename Compare>
  template <typename InputIterator>
  inline BaseTree<T, Node, Compare>::BaseTree(InputIterator begin, InputIterator end, const Compare& compare):
    m_root (NULL),
    m_compare (compare)
  {
    insert_all(begin, end);
  }

  template <typename T, typename Node, typename Compare>
  inline void element_direction(Node* current, const T& element)
  {
    if (m_compare(current, element)) {
      return TREE_LEFT;
    } else {
      return TREE_RIGHT;
    }
  }

  template <typename T, typename Node, typename Compare>
  inline BaseTree<T, Node, Compare>::~BaseTree()
  {
    clear();
  }

  template <typename T, typename Node, typename Compare>
  inline BaseTree<T, Node, Compare>& BaseTree<T, Node, Compare>::operator=(const BaseTree<T, Node, Compare>& other)
  {
    if ((&other) == this) {
      return *this;
    }
    clear();
    insert_all(other.begin(), other.end());
    return *this;
  }

  template <typename T, typename Node, typename Compare>
  inline bool BaseTree<T, Node, Compare>::operator==(const BaseTree<T, Node, Compare>& other) const
  {
    if (size() != other.size()) {
      return false;
    }
    const_iterator other_it (other.begin()), it (begin());
    for (; it != end(); ++it, ++other_it) {
      if (!(*it == *other_it)) {
        return false;
      }
    }
    return true;
  }

  template <typename T, typename Node, typename Compare>
  inline void BaseTree<T, Node, Compare>::clear()
  {
    if (m_root == NULL) {
      return;
    }
    Node* current = m_root;
    while (!(current->is_root() && current->is_leaf())) {
      if (current->is_leaf()) {
        assert(current != m_root);
        assert(current->parent != NULL);
        assert(current->parent_direction == TREE_LEFT || current->parent_direction == TREE_RIGHT);
        direction dir = current->parent_direction;
        current = current->parent;
        delete current->children[dir];
        current->children[dir] = NULL;
      } else {
        if (current->children[TREE_LEFT] != NULL) {
          current = current->children[TREE_LEFT];
        } else {
          assert(current->children[TREE_RIGHT] != NULL);
          current = current->children[TREE_RIGHT];
        }
      }
    }
    delete m_root;
    m_root = NULL;
  }
  template <typename T, typename Node, typename Compare>
  inline Node* BaseTree<T, Node, Compare>::internal_insert(const T& element)
  {
    if (m_root == NULL) {
      Node* new_node = new Node(element);
      m_root = new_node;
      return new_node;
    }
    Node* current = m_root;
    direction dir = BaseTree<T, Node, Compare>::element_direction(m_root, element);
    ++(current->size);
    while (current->children[dir] != NULL) {
      current = current->children[dir];
      dir = element_direction(current, element);
      ++(current->size);
    }
    Node* new_node = new Node(element, current, dir);
    current->children[dir] = new_node;
    return new_node;
  }

  template <typename T, typename Node, typename Compare>
  template <typename InputIterator>
  inline void BaseTree<T, Node, Compare>::insert_all(InputIterator begin, InputIterator end)
  {
    for (InputIterator it = begin; it != end; ++it) {
      insert(*it);
    }
  }

  template <typename T, typename Node, typename Compare>
  typename BaseTree<T, Node, Compare>::iterator BaseTree<T, Node, Compare>::lower_bound(const T& element)
  {
    Node* current = m_root;
    size_type correct_index = size();
    size_type left_size = 0;
    while (current != NULL) {
      if (m_compare(current->element, element)) {
        left_size += 1 + current->dir_size(TREE_LEFT);
        current = current->children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->dir_size(TREE_LEFT);
        current = current->children[TREE_LEFT];
      }
    }
    return iterator(this, correct_index);
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::const_iterator BaseTree<T, Node, Compare>::lower_bound(const T& element) const
  {
    Node* current = m_root;
    size_type correct_index = size();
    size_type left_size = 0;
    while (current != NULL) {
      if (m_compare(current->element, element)) {
        left_size += 1 + current->dir_size(TREE_LEFT);
        current = current->children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->dir_size(TREE_LEFT);
        current = current->children[TREE_LEFT];
      }
    }
    return const_iterator (this, correct_index);
  }

  template <typename T, typename Node, typename Compare>
  typename BaseTree<T, Node, Compare>::iterator BaseTree<T, Node, Compare>::upper_bound(const T& element)
  {
    Node* current = m_root;
    size_type correct_index = size();
    size_type left_size = 0;
    while (current != NULL) {
      if (current->element <= element) {
        left_size += 1 + current->dir_size(TREE_LEFT);
        current = current->children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->dir_size(TREE_LEFT);
        current = current->children[TREE_LEFT];
      }
    }
    return iterator(this, correct_index);
  }

  template <typename T, typename Node, typename Compare>
  typename BaseTree<T, Node, Compare>::const_iterator BaseTree<T, Node, Compare>::upper_bound(const T& element) const
  {
    Node* current = m_root;
    size_type correct_index = size();
    size_type left_size = 0;
    while (current != NULL) {
      if (current->element <= element) {
        left_size += 1 + current->dir_size(TREE_LEFT);
        current = current->children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->dir_size(TREE_LEFT);
        current = current->children[TREE_LEFT];
      }
    }
    return const_iterator (this, correct_index);
  }

  template <typename T, typename Node, typename Compare>
  inline typename std::pair< typename BaseTree<T, Node, Compare>::iterator, typename BaseTree<T, Node, Compare>::iterator > BaseTree<T, Node, Compare>::equal_range(const T &element)
  {
    return make_pair(lower_bound(element), upper_bound(element));
  }

  template <typename T, typename Node, typename Compare>
  inline typename std::pair< typename BaseTree<T, Node, Compare>::const_iterator, typename BaseTree<T, Node, Compare>::const_iterator > BaseTree<T, Node, Compare>::equal_range(const T &element) const
  {
    return make_pair(lower_bound(element), upper_bound(element));
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::size_type BaseTree<T, Node, Compare>::remove_all(const T &element)
  {
    // TODO efficiency
    size_type result;
    for (result = 0; remove(element); ++result);
    return result;
  }

  template <typename T, typename Node, typename Compare>
  inline bool BaseTree<T, Node, Compare>::remove(const T& element)
  {
    Node* current = m_root;
    while (current != NULL) {
      if (current->element == element) {
        while (current->is_inner()) {
          direction dir = current->min_size_direction();
          rotate(current, dir);
        }
        non_inner_remove(current);
        return true;
      }
      direction dir = element_direction(current, element);
      current = current->children[dir];
    }
    return false;
  }

  template <typename T, typename Node, typename Compare>
  inline void BaseTree<T, Node, Compare>::non_inner_remove(Node* node)
  {
    assert(node != NULL);
    assert(!(node->is_inner()));
    Node* parent = node->parent;
    direction dir = node->parent_direction;
    Node* child = NULL;
    if (!node->is_leaf()) {
      if (node->children[TREE_LEFT] == NULL) {
        child = node->children[TREE_RIGHT];
      } else {
        assert(node->children[TREE_RIGHT] == NULL);
        child = node->children[TREE_LEFT];
      }
      assert(child != NULL);
      child->parent = parent;
      child->parent_direction = dir;
    }
    delete node;
    if (parent == NULL) {
      m_root = child;
    } else {
      parent->children[dir] = child;
    }
    assert_pointers(parent);
    assert_pointers(child);
    while (parent != NULL) {
      --(parent->size);
      parent = parent->parent;
    }
  }

  template <typename T, typename Node, typename Compare>
  inline void BaseTree<T, Node, Compare>::rotate(Node* node, direction dir)
  {
    // Precondition
    assert(node != NULL);
    assert(node->children[dir] != NULL);

    // Define a few aliases
    Node* parent = node->parent;
    Node* new_node = node->children[dir];
    Node* new_node_child = new_node->children[1 - dir];
    direction parent_direction = node->parent_direction;
    size_type lost_child_size = new_node->dir_size(dir);

    // Change the pointers
    if (node->is_root()) {
      m_root = new_node;
    } else {
      parent->children[parent_direction] = new_node;
    }
    new_node->children[1 - dir] = node;
    new_node->parent = parent;
    new_node->parent_direction = parent_direction;
    node->children[dir] = new_node_child;
    node->parent = new_node;
    node->parent_direction = 1 - dir;
    if (new_node_child != NULL) {
      new_node_child->parent = node;
      new_node_child->parent_direction = dir;
    }

    // Correct the sizes
    size_type old_size = node->size;
    node->size -= 1 + lost_child_size;
    new_node->size = old_size;

    // Postcondition
    assert_pointers(new_node);
    assert_pointers(node);
    assert_pointers(parent);
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::size_type BaseTree<T, Node, Compare>::size() const
  {
    return m_root == NULL ? 0 : m_root->size;
  }

  template <typename T, typename Node, typename Compare>
  inline bool BaseTree<T, Node, Compare>::is_empty() const
  {
    return m_root == NULL;
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::iterator BaseTree<T, Node, Compare>::begin()
  {
    return iterator(this, 0);
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::iterator BaseTree<T, Node, Compare>::end()
  {
    return iterator(this, size());
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::const_iterator BaseTree<T, Node, Compare>::begin() const
  {
    return const_iterator(this, 0);
  }

  template <typename T, typename Node, typename Compare>
  inline typename BaseTree<T, Node, Compare>::const_iterator BaseTree<T, Node, Compare>::end() const
  {
    return const_iterator(this, size());
  }

}

#endif // DATASTRUCTURES_BASETREE_HPP
