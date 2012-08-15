#ifndef BINARYBASETREE_H
#define BINARYBASETREE_H

#include <sstream>
#include <stdexcept>
#include "basetypes.h"
#include "DataStructures_global.h"

namespace DataStructures {

  template <typename T, typename Node>
  std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node>& it);

  template <typename T, typename Node>
  class BaseTree
  {
    friend std::ostream& operator<< <> (std::ostream& out, const BaseTree<T, Node>& it);
  public:
    typedef typename Node::const_iterator const_iterator;

    typedef typename Node::iterator iterator;

  private:
    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

    typedef typename iterator::NodeInfo NodeInfo;

    typedef typename TreeNode<T>::NodePointer NodePointer;

  public:
    typedef std::out_of_range range_error;

    BaseTree();

    BaseTree(const BaseTree<T, Node>& other);

    template <typename Begin, typename End>
    BaseTree(Begin begin, End end);

    virtual ~BaseTree();

    BaseTree& operator=(const BaseTree<T, Node>& other);

    bool operator==(const BaseTree<T, Node>& other) const;

    inline bool operator!=(const BaseTree<T, Node>& other) const { return !operator==(other); }

    void clear();

    void merge(const BaseTree<T, Node>& other);

    void insert(const T& element);

    template <typename Begin, typename End>
    void insert_all(const Begin& begin, const End& end);

    bool search(const T& element) const { return m_root == NULL ? false : m_root->search(element); }

    iterator lower_bound(const T& element);

    iterator upper_bound(const T& element);

    std::pair< iterator, iterator > equal_range(const T& element);

    T& operator[](index_type index);

    const_iterator lower_bound(const T& element) const;

    const_iterator upper_bound(const T& element) const;

    std::pair< const_iterator, const_iterator > equal_range(const T& element) const;

    const T& operator[](index_type index) const;

    bool remove(const T& element);

    index_type remove_all(const T& element);

    inline index_type size() const { return m_root == NULL ? 0 : m_root->size(); }

    iterator begin() { return m_root == NULL ? iterator() : m_root->begin(); }

    iterator end() { return m_root == NULL ? iterator() : m_root->end(); }

    const_iterator begin() const { return m_root == NULL ? const_iterator() : m_root->begin(); }

    const_iterator end() const { return m_root == NULL ? const_iterator() : m_root->end(); }

  protected:
    TreeNode<T>* m_root;

  };

  template <typename T, typename Node>
  BaseTree<T, Node>::BaseTree():
    m_root (NULL)
  {
  }

  template <typename T, typename Node>
  BaseTree<T, Node>::BaseTree(const BaseTree<T, Node>& other)
  {
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new Node(static_cast<const Node&>(*other.m_root));
    }
  }

  template <typename T, typename Node>
  template <typename Begin, typename End>
  BaseTree<T, Node>::BaseTree(Begin begin, End end):
    m_root (NULL)
  {
    insert_all(begin, end);
  }

  template <typename T, typename Node>
  BaseTree<T, Node>::~BaseTree()
  {
    delete m_root;
  }

  template <typename T, typename Node>
  BaseTree<T, Node>& BaseTree<T, Node>::operator=(const BaseTree<T, Node>& other)
  {
    if ((&other) == this) {
      return *this;
    }
    delete m_root;
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new Node(static_cast<const Node&>(*other.m_root));
    }
    return *this;
  }

  template <typename T, typename Node>
  bool BaseTree<T, Node>::operator==(const BaseTree<T, Node>& other) const
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
  void BaseTree<T, Node>::clear()
  {
    if (m_root != NULL) {
      delete m_root;
      m_root = NULL;
    }
  }

  template <typename T, typename Node>
  void BaseTree<T, Node>::merge(const BaseTree<T, Node> &other)
  {
    insert_all(other.begin(), other.end());
  }

  template <typename T, typename Node>
  void BaseTree<T, Node>::insert(const T& element)
  {
    if (m_root == NULL) {
      m_root = new Node(element);
    } else {
      m_root = m_root->insert(element);
    }
  }

  template <typename T, typename Node>
  template <typename BeginIterator, typename EndIterator>
  void BaseTree<T, Node>::insert_all(const BeginIterator& begin, const EndIterator& end)
  {
    for (BeginIterator it = begin; it != end; ++it) {
      insert(*it);
    }
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::iterator BaseTree<T, Node>::lower_bound(const T &element)
  {
    if (m_root == NULL) {
      return iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->lower_bound(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::const_iterator BaseTree<T, Node>::lower_bound(const T &element) const
  {
    if (m_root == NULL) {
      return const_iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->lower_bound(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::iterator BaseTree<T, Node>::upper_bound(const T &element)
  {
    if (m_root == NULL) {
      return iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->upper_bound(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  typename BaseTree<T, Node>::const_iterator BaseTree<T, Node>::upper_bound(const T &element) const
  {
    if (m_root == NULL) {
      return const_iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->upper_bound(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  typename std::pair< typename BaseTree<T, Node>::iterator, typename BaseTree<T, Node>::iterator > BaseTree<T, Node>::equal_range(const T &element)
  {
    if (m_root == NULL) {
      return make_pair(iterator(), iterator());
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->equal_range(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  typename std::pair< typename BaseTree<T, Node>::const_iterator, typename BaseTree<T, Node>::const_iterator > BaseTree<T, Node>::equal_range(const T &element) const
  {
    if (m_root == NULL) {
      return make_pair(const_iterator(), const_iterator());
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->equal_range(empty_info, element, 0);
    }
  }

  template <typename T, typename Node>
  bool BaseTree<T, Node>::remove(const T& element)
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
  index_type BaseTree<T, Node>::remove_all(const T& element)
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
  T& BaseTree<T, Node>::operator[](index_type index)
  {
    if (index >= size()) {
      std::ostringstream oss;
      oss << "Invalid index " << index << " for BaseTree of size " << size() << ".";
      throw range_error(oss.str());
    }
    return m_root->operator[](index);
  }

  template <typename T, typename Node>
  const T& BaseTree<T, Node>::operator[](index_type index) const
  {
    if (index >= size()) {
      std::ostringstream oss;
      oss << "Invalid index " << index << " for BaseTree of size " << size() << ".";
      throw range_error(oss.str());
    }
    return m_root->operator[](index);
  }

  template <typename T, typename Node>
  std::ostream& operator<<(std::ostream& out, const BaseTree<T, Node>& BaseTree)
  {
    out << "BaseTree[";
    if (BaseTree.m_root != NULL) {
      out << *(BaseTree.m_root);
    }
    out << "]";
    return out;
  }

}

#endif // BINARYBASETREE_H
