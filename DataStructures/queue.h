#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"

namespace DataStructures {
  
  template <typename T>
  class Queue<T> : public DataStructures::BaseList<T>
  {
  public:
    typedef ListIterator<T, Queue<T> > iterator;

    typedef ListConstIterator<T, Queue<T> > const_iterator;

    Queue();

    Queue(const Queue<T>& other);

    template <typename BeginIterator, typename EndIterator>
    void push_all(const BeginIterator& begin, const EndIterator& end);

    const T& operator[](index_type i) const;

    T& operator[](index_type i);

    void push(const T& element);

    T pop();

    T top() const;

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, m_size); }

    inline const_iterator end() const { return const_iterator(this, m_size); }

  protected:
    void copy_old_content(const DataStructures::T *old_content);

  private:

    index_type m_begin;

    index_type m_end;
  };

  Queue<T>::Queue():
    BaseList ()
  {
  }

  Queue<T>::Queue(const Queue<T> &other):
    BaseList (other)
  {
  }

  void Queue<T>::push_all(const BeginIterator& begin, const EndIterator& end)
  {

  }

  void Queue<T>::push(const T &element)
  {

  }

  template <typename T>
  bool Queue<T>::operator==(const ArrayList<T> other) const
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
  const T& Queue<T>::operator[](index_type i) const
  {
    check_index(i);
    return m_content[(i + m_begin) % m_capacity];
  }

  template <typename T>
  T& Queue<T>::operator[](index_type i)
  {
    check_index(i);
    return m_content[i];
  }

  template <typename T>
  void Queue<T>::push(const T& element)
  {
    prepare_size(m_size + 1);
    m_content[m_size - 1] = element;
  }

  template <typename T>
  T Queue<T>::pop()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot pop from an empty ArrayList.");
    }
    T element = m_content[m_size - 1];
    prepare_size(m_size - 1);
    return element;
  }

  template <typename T>
  T& Queue<T>::top()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return m_content[m_size - 1];
  }

  template <typename T>
  const T& Queue<T>::top() const
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return m_content[m_size - 1];
  }

  void Queue<T>::copy_old_content(const T* old_content)
  {
    if (m_end > m_begin) {
      add_content(m_content, old_content + m_begin, m_end - m_begin);
    } else {
      add_content(m_content, old_content + m_begin, m_size - m_begin);
      add_content(m_content, old_content, m_end);
    }
  }

}

#endif // DATASTRUCTURES_QUEUE_H
