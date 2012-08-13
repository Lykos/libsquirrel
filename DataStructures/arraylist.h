#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"
#include <cassert>

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT ArrayList
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, ArrayList<T> > iterator;

    typedef ListConstIterator<T, ArrayList<T> > const_iterator;

    explicit ArrayList(index_type initial_size = 0, const T& element = T());

    ArrayList(const ArrayList<T>& other);
/*
    template <typename BeginIterator, typename EndIterator>
    ArrayList(const BeginIterator& begin, const EndIterator& end);*/

    template <typename BeginIterator, typename EndIterator>
    void push_all(const BeginIterator& begin, const EndIterator& end);

    ArrayList<T> operator+(const ArrayList<T>& other) const;

    ArrayList<T>& operator+=(const ArrayList<T>& other);

    ArrayList<T> operator*(index_type factor) const;

    ArrayList<T>& operator*=(index_type factor);

    bool operator==(const ArrayList<T> other) const;

    const T& operator[](index_type i) const;

    T& operator[](index_type i);

    void push(const T& element);

    T pop();

    const T& top() const;

    T& top();

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::m_size); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::m_size); }

  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const ArrayList<T>& list)
  {
    out << "[";
    for (typename ArrayList<T>::const_iterator it = list.begin(); it != list.end(); it++) {
      out << *it;
      if (it + 1 != list.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  ArrayList<T>::ArrayList(index_type initial_size, const T& element):
    BaseList(initial_size, element)
  {
  }

/*
  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  ArrayList<T>::ArrayList(const BeginIterator& begin, const EndIterator& end):
    m_size(end - begin),
    m_min_capacity(DEFAULT_MIN_CAPACITY)
  {
    init_capacity(end - begin);
    index_type i = 0;
    for (BeginIterator it = begin; it < end; ++it) {
      m_content[i++] = *it;
    }
  }
*/

  template <typename T>
  template <typename BeginIterator, typename EndIterator>
  void ArrayList<T>::push_all(const BeginIterator& begin, const EndIterator& end)
  {
    index_type i = m_size;
    prepare_size(m_size + (end - begin));
    for (BeginIterator it = begin; it != end; ++it) {
      m_content[i++] = *it;
    }
  }

  template <typename T>
  ArrayList<T>::ArrayList(const ArrayList<T>& other):
    BaseList(other)
  {
  }

  template <typename T>
  ArrayList<T> ArrayList<T>::operator+(const ArrayList<T>& other) const
  {
    ArrayList<T> result(m_size + other.m_size);
    result.add_content(m_content, 0, m_size);
    result.add_content(other.m_content, m_size, other.m_size);
    return result;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator+=(const ArrayList<T>& other)
  {
    index_type old_size = m_size;
    prepare_size(m_size + other.m_size);
    add_content(other.m_content, old_size, other.m_size);
    return *this;
  }

  template <typename T>
  ArrayList<T> ArrayList<T>::operator*(index_type factor) const
  {
    ArrayList<T> result (m_size * factor);
    for (index_type i = 0; i < factor; ++i) {
      result.add_content(m_content, i * m_size, m_size);
    }
    return result;
  }

  template <typename T>
  ArrayList<T>& ArrayList<T>::operator*=(index_type factor)
  {
    index_type old_size = m_size;
    prepare_size(m_size * factor);
    for (index_type i = 1; i < factor; ++i) {
      add_content(m_content, i * old_size, old_size);
    }
    return *this;
  }

  template <typename T>
  bool ArrayList<T>::operator==(const ArrayList<T> other) const
  {
    if (size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < size(); ++i) {
      if (m_content[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  const T& ArrayList<T>::operator[](index_type i) const
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  T& ArrayList<T>::operator[](index_type i)
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  void ArrayList<T>::push(const T& element)
  {
    prepare_size(m_size + 1);
    m_content[m_size - 1] = element;
  }

  template <typename T>
  T ArrayList<T>::pop()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot pop from an empty ArrayList.");
    }
    T element = m_content[m_size - 1];
    prepare_size(m_size - 1);
    return element;
  }

  template <typename T>
  T& ArrayList<T>::top()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return m_content[m_size - 1];
  }

  template <typename T>
  const T& ArrayList<T>::top() const
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return m_content[m_size - 1];
  }

}

#endif // ARRAYLIST_H
