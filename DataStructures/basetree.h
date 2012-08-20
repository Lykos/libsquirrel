#ifndef DATASTRUCTURES_BASETREE_H
#define DATASTRUCTURES_BASETREE_H

#include <sstream>
#include <stdexcept>
#include <cassert>
#include "basetypes.h"
#include "treeiterator.h"
#include "treeconstiterator.h"
#include "DataStructures_global.h"

#ifndef NDEBUG
#define tree_check_index(index) if (index >= BaseTree<T, Node>::size()) { std::ostringstream oss; oss << "Invalid index " << index << " for BaseTree of size " << BaseTree<T, Node>::size() << "."; throw typename BaseTree<T, Node>::range_error(oss.str()); }
#else
#define tree_check_index(index)
#endif
#define assert_size(node_pointer) assert(node_pointer->m_size == node_pointer->calculated_size())

namespace DataStructures {

  template <typename T, typename Node>
  std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node>& it);

  template <typename T, typename Node>
  class BaseTree
  {
    friend std::ostream& operator<< <> (std::ostream& out, const BaseTree<T, Node>& it);

    friend class TreeConstIterator<T, BaseTree<T, Node> >;

    friend class TreeIterator<T, BaseTree<T, Node> >;

  public:
    typedef TreeConstIterator<T, BaseTree<T, Node> > const_iterator;

    typedef TreeIterator<T, BaseTree<T, Node> > iterator;

    typedef bool (*predicate_t)(const T&);

  protected:
    typedef Node* NodePointer;

    typedef typename Node::direction direction;

  public:
    typedef std::out_of_range range_error;

    inline BaseTree();

    inline BaseTree(const BaseTree<T, Node>& other);

    template <typename Iterator>
    inline BaseTree(Iterator begin, Iterator end);

    inline virtual ~BaseTree();

    inline BaseTree& operator=(const BaseTree<T, Node>& other);

    inline bool operator==(const BaseTree<T, Node>& other) const;

    inline bool operator!=(const BaseTree<T, Node>& other) const { return !operator==(other); }

    inline void clear();

    inline void merge(const BaseTree<T, Node>& other);

    inline virtual void insert(const T& element);

    template <typename Iterator>
    inline void insert_all(const Iterator& begin, const Iterator& end);

    inline bool search(const T& element) const;

    inline iterator lower_bound(const T& element);

    inline iterator upper_bound(const T& element);

    inline std::pair< iterator, iterator > equal_range(const T& element);

    inline T& operator[](index_type index);

    inline const_iterator lower_bound(const T& element) const;

    inline const_iterator upper_bound(const T& element) const;

    inline std::pair< const_iterator, const_iterator > equal_range(const T& element) const;

    inline const T& operator[](index_type index) const;

    inline bool remove(const T& element);

    inline index_type remove_all(const T& element);

    inline index_type size() const { return m_root == NULL ? 0 : m_root->size(); }

    inline iterator begin() { return iterator(this, 0); }

    inline iterator end() { return iterator(this, size()); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline const_iterator end() const { return const_iterator(this, size()); }

  protected:
    NodePointer m_root;

    typedef struct {
      NodePointer node;
      direction dir;
    } way_point_t;

    typedef ArrayList<way_point_t> parent_stack_t;

    inline void insert_with_stack(NodePointer current, const T& element, parent_stack_t& parent_stack);

    inline void rotate(NodePointer parent, direction parent_direction, direction dir);

    inline void rotate_root(direction dir);

  };

  template <typename T, typename Node>
  inline std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node>& tree)
  {
    out << "BaseTree[";
    for (typename BaseTree<T, Node>::const_iterator it = tree.begin(); it < tree.end(); ++it) {
      out << (*it).get_element();
      if (it + 1 < tree.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T, typename Node>
  inline bool BaseTree<T, Node>::search(const T& element) const
  {
    NodePointer current = m_root;
    while (current != NULL) {
      if (current->get_element() == element) {
        return true;
      }
      direction dir = current->element_direction(element);
      current = current->child(dir);
    }
    return false;
  }

  template <typename T, typename Node>
  inline const T& BaseTree<T, Node>::operator[](index_type index) const
  {
    tree_check_index(index);
    NodePointer current = m_root;
    while (true) {
      assert(current != NULL);
      assert(index < current->size());
      index_type left = current->size(TREE_LEFT);
      if (index < left) {
        current = current->child(TREE_LEFT);
      } else if (index > left) {
        index -= left + 1;
        current = current->child(TREE_RIGHT);
      } else {
        return current->get_element();
      }
    }
  }

  template <typename T, typename Node>
  inline T& BaseTree<T, Node>::operator[](index_type index)
  {
    tree_check_index(index);
    NodePointer current = m_root;
    while (true) {
      assert(current != NULL);
      assert(index < current->size());
      index_type left = current->size(TREE_LEFT);
      if (index < left) {
        current = current->child(TREE_LEFT);
      } else if (index > left) {
        index -= left + 1;
        current = current->child(TREE_RIGHT);
      } else {
        return current->get_element();
      }
    }
  }

  template <typename T, typename Node>
  inline BaseTree<T, Node>::BaseTree():
    m_root (NULL)
  {
  }

  template <typename T, typename Node>
  inline BaseTree<T, Node>::BaseTree(const BaseTree<T, Node>& other)
  {
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new Node(static_cast<const Node&>(*other.m_root));
    }
  }

  template <typename T, typename Node>
  template <typename Iterator>
  inline BaseTree<T, Node>::BaseTree(Iterator begin, Iterator end):
    m_root (NULL)
  {
    insert_all(begin, end);
  }

  template <typename T, typename Node>
  inline BaseTree<T, Node>::~BaseTree()
  {
    clear();
  }

  template <typename T, typename Node>
  inline BaseTree<T, Node>& BaseTree<T, Node>::operator=(const BaseTree<T, Node>& other)
  {
    if ((&other) == this) {
      return *this;
    }
    clear();
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new Node(*other.m_root);
    }
    return *this;
  }

  template <typename T, typename Node>
  inline bool BaseTree<T, Node>::operator==(const BaseTree<T, Node>& other) const
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

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::clear()
  {
    if (m_root == NULL) {
      return;
    }
    ArrayList<NodePointer> deletion_stack (1, m_root);
    while (!deletion_stack.is_empty()) {
      NodePointer current = deletion_stack.back();
      if (current->childless()) {
        deletion_stack.pop();
      } else {
        for (direction dir = TREE_LEFT; dir <= TREE_RIGHT; ++dir) {
          if (current->m_children[dir] != NULL) {
            if (current->m_children[dir]->childless()) {
              delete current->m_children[dir];
              current->m_children[dir] = NULL;
            } else {
              deletion_stack.push(current->child(dir));
            }
          }
        }
      }
    }
    delete m_root;
    m_root = NULL;
  }

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::merge(const BaseTree<T, Node> &other)
  {
    insert_all(other.begin(), other.end());
  }

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::insert(const T& element)
  {
    if (m_root == NULL) {
      m_root = new Node(element);
      return;
    }
    NodePointer current = m_root;
    direction dir = m_root->element_direction(element);
    while (current->m_children[dir] != NULL) {
      ++(current->m_size);
      current = current->child(dir);
      dir = current->element_direction(element);
    }
    current->m_children[dir] = new Node(element);
  }

  template <typename T, typename Node>
  template <typename Iterator>
  inline void BaseTree<T, Node>::insert_all(const Iterator& begin, const Iterator& end)
  {
    for (Iterator it = begin; it != end; ++it) {
      insert(*it);
    }
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::iterator BaseTree<T, Node>::lower_bound(const T& element)
  {
    NodePointer current = m_root;
    index_type correct_index = size();
    index_type left_size = 0;
    while (current != NULL) {
      if (current->get_element() < element) {
        left_size += 1 + current->size(TREE_LEFT);
        current = current->child(TREE_RIGHT);
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->child(TREE_LEFT);
      }
    }
    return iterator (this, correct_index);
  }

  template <typename T, typename Node>
  inline typename BaseTree<T, Node>::const_iterator BaseTree<T, Node>::lower_bound(const T& element) const
  {
    NodePointer current = m_root;
    index_type correct_index = size();
    index_type left_size = 0;
    while (current != NULL) {
      if (current->get_element() < element) {
        left_size += 1 + current->size(TREE_LEFT);
        current = current->child(TREE_RIGHT);
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->child(TREE_LEFT);
      }
    }
    return const_iterator (this, correct_index);
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::iterator BaseTree<T, Node>::upper_bound(const T& element)
  {
    NodePointer current = m_root;
    index_type correct_index = size();
    index_type left_size = 0;
    while (current != NULL) {
      if (current->get_element() <= element) {
        left_size += 1 + current->size(TREE_LEFT);
        current = current->child(TREE_RIGHT);
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->child(TREE_LEFT);
      }
    }
    return iterator (this, correct_index);
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::const_iterator BaseTree<T, Node>::upper_bound(const T& element) const
  {
    NodePointer current = m_root;
    index_type correct_index = size();
    index_type left_size = 0;
    while (current != NULL) {
      if (current->get_element() <= element) {
        left_size += 1 + current->size(TREE_LEFT);
        current = current->child(TREE_RIGHT);
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->child(TREE_LEFT);
      }
    }
    return const_iterator (this, correct_index);
  }

  template <typename T, typename Node>
  inline typename std::pair< typename BaseTree<T, Node>::iterator, typename BaseTree<T, Node>::iterator > BaseTree<T, Node>::equal_range(const T &element)
  {
    return make_pair(lower_bound(element), upper_bound(element));
  }

  template <typename T, typename Node>
  inline typename std::pair< typename BaseTree<T, Node>::const_iterator, typename BaseTree<T, Node>::const_iterator > BaseTree<T, Node>::equal_range(const T &element) const
  {
    return make_pair(lower_bound(element), upper_bound(element));
  }

  template <typename T, typename Node>
  inline bool BaseTree<T, Node>::remove(const T& element)
  {
    if (m_root == NULL) {
      return false;
    } else {
      std::pair<NodePointer, bool> result = m_root->remove(element);
      m_root = result.first;
      return result.second;
    }
  }

  template <typename T, typename Node>
  inline index_type BaseTree<T, Node>::remove_all(const T& element)
  {
    /*
    if (m_root == NULL) {
      return 0;
    } else {
      std::pair<NodePointer, index_type> result = m_root->remove_all(element);
      m_root = result.first;
      return result.second;
    }*/
    return 0;
  }

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::rotate(NodePointer parent, direction parent_direction, direction dir)
  {
    // Precondition
    assert(parent != NULL);
    assert(parent->m_children[parent_direction] != NULL);
    assert(parent->m_children[parent_direction]->m_children[dir] != NULL);

    // Define a few aliases
    NodePointer old_current = parent->child(parent_direction);
    NodePointer new_current = old_current->child(dir);
    NodePointer new_this_child = new_current->child(1 - dir);
    index_type lost_child_size = new_current->size(dir);

    // Change the pointers
    new_current->m_children[1 - dir] = old_current;
    old_current->m_children[dir] = new_this_child;
    parent->m_children[parent_direction] = new_current;

    // Correct the sizes
    index_type old_size = old_current->m_size;
    old_current->m_size -= 1 + lost_child_size;
    new_current->m_size = old_size;

    // Postcondition
    assert_size(new_current);
    assert_size(old_current);
  }

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::rotate_root(direction dir)
  {
    // TODO Refactor and reuse code from rotate

    // Precondition
    assert(m_root != NULL);
    assert(m_root->m_children[dir] != NULL);

    // Define a few aliases
    NodePointer old_root = m_root;
    NodePointer new_root = old_root->child(dir);
    NodePointer new_this_child = new_root->child(1 - dir);
    index_type lost_child_size = new_root->size(dir);

    // Change the pointers
    new_root->m_children[1 - dir] = old_root;
    old_root->m_children[dir] = new_this_child;
    m_root = new_root;

    // Correct the sizes
    index_type old_size = old_root->m_size;
    old_root->m_size -= 1 + lost_child_size;
    new_root->m_size = old_size;

    // Postcondition
    assert_size(new_root);
    assert_size(old_root);
  }

  template <typename T, typename Node>
  inline void BaseTree<T, Node>::insert_with_stack(NodePointer current, const T& element, parent_stack_t& parent_stack)
  {
    while (current != NULL) {
      ++(current->m_size);
      direction dir = current->element_direction(element);
      way_point_t way_point {current, dir};
      parent_stack.push(way_point);
      current = current->child(dir);
    }
    NodePointer last = parent_stack.back().node;
    direction last_dir = parent_stack.back().dir;
    last->m_children[last_dir] = new Node(element);
  }

}

#endif // DATASTRUCTURES_BASETREE_H
