#ifndef TREAP_H
#define TREAP_H

#include <sstream>
#include "basetypes.h"
#include "DataStructures_global.h"
#include "treapnode.h"

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Treap<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Treap<T>& it);
  public:
    typedef typename TreapNode<T>::const_iterator const_iterator;

    typedef typename TreapNode<T>::iterator iterator;

  private:
    typedef typename const_iterator::ConstNodeInfo ConstNodeInfo;

    typedef typename iterator::NodeInfo NodeInfo;

  public:
    typedef std::out_of_range range_error;

    Treap();

    Treap(const Treap& other);

    template <typename BeginIterator, typename EndIterator>
    Treap(BeginIterator begin, EndIterator end);

    virtual ~Treap();

    Treap& operator=(const Treap& other);

    bool operator==(const Treap& other) const;

    bool operator!=(const Treap& other) const { return !operator==(other); }

    void clear();

    void merge(const Treap<T>& other);

    void insert(const T& element);

    template <typename BeginIterator, typename EndIterator>
    void insert_all(const BeginIterator& begin, const EndIterator& end);

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

  private:
    TreapNode<T>* m_root;

  };

  template <typename T>
  Treap<T>::Treap():
    m_root (NULL)
  {
  }

  template <typename T>
  Treap<T>::Treap(const Treap<T>& other)
  {
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new TreapNode<T>(*other.m_root);
    }
  }

  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  Treap<T>::Treap(BeginIterator begin, EndIterator End):
    m_root (NULL)
  {
    insert_all(begin, end);
  }

  template <typename T>
  Treap<T>::~Treap()
  {
    delete m_root;
  }

  template <typename T>
  Treap<T>& Treap<T>::operator=(const Treap<T>& other)
  {
    if ((&other) == this) {
      return *this;
    }
    delete m_root;
    if (other.m_root == NULL) {
      m_root = NULL;
    } else {
      m_root = new TreapNode<T>(*other.m_root);
    }
    return *this;
  }

  template <typename T>
  bool Treap<T>::operator==(const Treap<T>& other) const
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

  template <typename T>
  void Treap<T>::clear()
  {
    if (m_root != NULL) {
      delete m_root;
      m_root = NULL;
    }
  }

  template <typename T>
  void Treap<T>::merge(const Treap<T> &other)
  {
    insert_all(other.begin(), other.end());
  }

  template <typename T>
  void Treap<T>::insert(const T& element)
  {
    if (m_root == NULL) {
      m_root = new TreapNode<T>(element);
    } else {
      m_root->insert(&m_root, element);
    }
  }

  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  void Treap<T>::insert_all(const BeginIterator& begin, const EndIterator& end)
  {
    for (BeginIterator it = begin; it != end; ++it) {
      insert(*it);
    }
  }

  template <typename T>
  typename Treap<T>::iterator Treap<T>::lower_bound(const T &element)
  {
    if (m_root == NULL) {
      return iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->lower_bound(empty_info, element, 0);
    }
  }

  template <typename T>
  typename Treap<T>::const_iterator Treap<T>::lower_bound(const T &element) const
  {
    if (m_root == NULL) {
      return const_iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->lower_bound(empty_info, element, 0);
    }
  }

  template <typename T>
  typename Treap<T>::iterator Treap<T>::upper_bound(const T &element)
  {
    if (m_root == NULL) {
      return iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->upper_bound(empty_info, element, 0);
    }
  }

  template <typename T>
  typename Treap<T>::const_iterator Treap<T>::upper_bound(const T &element) const
  {
    if (m_root == NULL) {
      return const_iterator();
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->upper_bound(empty_info, element, 0);
    }
  }

  template <typename T>
  typename std::pair< typename Treap<T>::iterator, typename Treap<T>::iterator > Treap<T>::equal_range(const T &element)
  {
    if (m_root == NULL) {
      return make_pair(iterator(), iterator());
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->equal_range(empty_info, element, 0);
    }
  }

  template <typename T>
  typename std::pair< typename Treap<T>::const_iterator, typename Treap<T>::const_iterator > Treap<T>::equal_range(const T &element) const
  {
    if (m_root == NULL) {
      return make_pair(const_iterator(), const_iterator());
    } else {
      ArrayList<NodeInfo> empty_info;
      return m_root->equal_range(empty_info, element, 0);
    }
  }

  template <typename T>
  bool Treap<T>::remove(const T& element)
  {
    if (m_root == NULL) {
      return false;
    } else {
      return m_root->remove(&m_root, element);
    }
  }

  template <typename T>
  index_type Treap<T>::remove_all(const T& element)
  {
    if (m_root == NULL) {
      return 0;
    } else {
      return m_root->remove_all(&m_root, element);
    }
  }

  template <typename T>
  T& Treap<T>::operator[](index_type index)
  {
    if (index >= size()) {
      std::ostringstream oss;
      oss << "Invalid index " << index << " for treap of size " << size() << ".";
      throw range_error(oss.str());
    }
    return m_root->operator[](index);
  }

  template <typename T>
  const T& Treap<T>::operator[](index_type index) const
  {
    if (index >= size()) {
      std::ostringstream oss;
      oss << "Invalid index " << index << " for treap of size " << size() << ".";
      throw range_error(oss.str());
    }
    return m_root->operator[](index);
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Treap<T>& treap)
  {
    out << "Treap[";
    if (treap.m_root != NULL) {
      out << *(treap.m_root);
    }
    out << "]";
    return out;
  }

}

#endif // TREAP_H
