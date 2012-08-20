#ifndef DATASTRUCTURES_BINARYBASETREE_H
#define DATASTRUCTURES_BINARYBASETREE_H

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

  private:
    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename TreeNode<T>::NodePointer NodePointer;

    typedef typename TreeNode<T>::direction direction;

    inline predicate_t negate_predicate(predicate_t predicate) { return [&predicate](const T& element) { return !predicate(element); }; }

  public:
    typedef std::out_of_range range_error;

    inline BaseTree();

    inline BaseTree(const BaseTree<T, Node>& other);

    template <typename Begin, typename End>
    inline BaseTree(Begin begin, End end);

    inline virtual ~BaseTree();

    inline BaseTree& operator=(const BaseTree<T, Node>& other);

    inline bool operator==(const BaseTree<T, Node>& other) const;

    inline bool operator!=(const BaseTree<T, Node>& other) const { return !operator==(other); }

    inline void clear();

    inline void merge(const BaseTree<T, Node>& other);

    inline void insert(const T& element);

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
    TreeNode<T>* m_root;

  };

  template <typename T, typename Node>
  inline bool BaseTree<T, Node>::search(const T& element) const
  {
    NodePointer current = m_root;
    while (current != NULL) {
      if (current->get_element() == element) {
        return true;
      }
      direction dir = current->element_direction(element);
      current = current->m_children[dir];
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
        current = current->m_children[TREE_LEFT];
      } else if (index > left) {
        index -= left + 1;
        current = current->m_children[TREE_RIGHT];
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
        current = current->m_children[TREE_LEFT];
      } else if (index > left) {
        index -= left + 1;
        current = current->m_children[TREE_RIGHT];
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
  template <typename Begin, typename End>
  inline BaseTree<T, Node>::BaseTree(Begin begin, End end):
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
      m_root = new Node(static_cast<const Node&>(*other.m_root));
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
              deletion_stack.push(current->m_children[dir]);
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
    } else {
      m_root = m_root->insert(element);
    }
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
        current = current->m_children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->m_children[TREE_LEFT];
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
        current = current->m_children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->m_children[TREE_LEFT];
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
        current = current->m_children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->m_children[TREE_LEFT];
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
        current = current->m_children[TREE_RIGHT];
      } else {
        correct_index = left_size + current->size(TREE_LEFT);
        current = current->m_children[TREE_LEFT];
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
    if (m_root == NULL) {
      return 0;
    } else {
      std::pair<NodePointer, index_type> result = m_root->remove_all(element);
      m_root = result.first;
      return result.second;
    }
  }


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

}

#endif // DATASTRUCTURES_BINARYBASETREE_H
