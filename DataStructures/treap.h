#ifndef TREAP_H
#define TREAP_H

#include <algorithm>
#include "DataStructures_global.h"
#include "treapnode.h"

namespace DataStructures {

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Treap
  {
  public:
    typedef typename TreapNode<T>::const_iterator const_iterator;

    typedef typename TreapNode<T>::iterator iterator;

    Treap();

    Treap(const Treap& other);

    template <typename BeginIterator, typename EndIterator>
    Treap(BeginIterator begin, EndIterator end);

    virtual ~Treap();

    Treap& operator=(const Treap& other);

    void clear();

    void merge(const Treap<T>& other);

    void insert(const T& element);

    template <typename BeginIterator, typename EndIterator>
    void insert_all(const BeginIterator& begin, const EndIterator& end);

    bool search(const T& element) const { return m_root == NULL ? false : m_root->search(element); }

    TreapIterator<T> lower_bound(const T& element) { return m_root == NULL ? TreapIterator<T>() : m_root->lower_bound(element); }

    TreapIterator<T> upper_bound(const T& element) { return m_root == NULL ? TreapIterator<T>() : m_root->upper_bound(element); }

    std::pair< TreapIterator<T>, TreapIterator<T> > equal_range(const T& element) { return m_root == NULL ? make_pair(TreapIterator<T>(), TreapIterator<T>()) : m_root->equal_range(element); }

    T& operator[](index_type index) { assert(m_root != NULL); return m_root->operator[](index); }

    TreapConstIterator<T> lower_bound(const T& element) const { return m_root == NULL ? TreapConstIterator<T>() : m_root->lower_bound(element); }

    TreapConstIterator<T> upper_bound(const T& element) const { return m_root == NULL ? TreapConstIterator<T>() : m_root->upper_bound(element); }

    std::pair< TreapConstIterator<T>, TreapConstIterator<T> > equal_range(const T& element) const { return m_root == NULL ? make_pair(TreapConstIterator<T>(), TreapConstIterator<T>()) : m_root->equal_range(element); }

    const T& operator[](index_type index) const { assert(m_root != NULL); return m_root->operator[](index); }

    bool remove(const T& element);

    index_type remove_all(const T& element);

    inline index_type size() const { return m_root == NULL ? 0 : m_root->size(); }

    TreapIterator<T> begin() { return m_root == NULL ? TreapIterator<T>() : m_root->begin(); }

    TreapIterator<T> end() { return m_root == NULL ? TreapIterator<T>() : m_root->end(); }

    TreapConstIterator<T> begin() const { return m_root == NULL ? TreapConstIterator<T>() : m_root->begin(); }

    TreapConstIterator<T> end() const { return m_root == NULL ? TreapConstIterator<T>() : m_root->end(); }

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
  Treap<T>& Treap<T>::operator=(const Treap& other)
  {
    if (&other == *this) {
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

}

#endif // TREAP_H
