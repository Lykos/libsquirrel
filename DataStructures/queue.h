#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"

namespace DataStructures {
  
  template <typename T>
  class Queue<T> : public BaseList<T>
  {
  public:
    typedef ListIterator<T, Queue<T> > iterator;

    typedef ListConstIterator<T, Queue<T> > const_iterator;

    Queue();

    Queue(const Queue<T>& other);

    operator==(const Queue<T>& other);

    operator!=(const Queue<T>& other) { return !operator==(other); }

    template <typename BeginIterator, typename EndIterator>
    void push_all(const BeginIterator& begin, const EndIterator& end);

    inline const T& operator[](index_type i) const { check_index(i); return BaseList<T>::m_content[(i + BaseList<T>::m_begin) % BaseList<T>::m_capacity]; }

    inline T& operator[](index_type i) const { check_index(i); return BaseList<T>::m_content[(i + BaseList<T>::m_begin) % BaseList<T>::m_capacity]; }

    void push(const T& element);

    T pop();

    T top() const;

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::m_size); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::m_size); }

  protected:
    void copy_old_content(const DataStructures::T *old_content);

  private:

    index_type m_begin;

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

  template <typename T>
  bool Queue<T>::operator==(const ArrayList<T> other) const
  {
    if (size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < size(); ++i) {
      if (operator[](i) != other.operator[](i)) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  const T& Queue<T>::operator[](index_type i) const
  {
    check_index(i);
    return BaseList<T>::m_content[(i + BaseList<T>::m_begin) % BaseList<T>::m_capacity];
  }

  template <typename T>
  T& Queue<T>::operator[](index_type i)
  {
    check_index(i);
    return BaseList<T>::m_content[(i + BaseList<T>::m_begin) % BaseList<T>::m_capacity];
  }

  template <typename T>
  void Queue<T>::push(const T& element)
  {
    prepare_size(BaseList<T>::m_size + 1);
    BaseList<T>::m_content[(BaseList<T>::m_size + BaseList<T>::m_begin - 1) % BaseList<T>::m_capacity] = element;
  }

  template <typename T>
  T Queue<T>::pop()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot pop from an empty ArrayList.");
    }
    T element = BaseList<T>::m_content[BaseList<T>::m_begin++];
    prepare_size(BaseList<T>::m_size - 1);
    return element;
  }

  template <typename T>
  T& Queue<T>::top()
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return BaseList<T>::m_content[BaseList<T>::m_begin];
  }

  template <typename T>
  const T& Queue<T>::top() const
  {
    if (is_empty()) {
      throw empty_list_error("Cannot take the top from an empty ArrayList.");
    }
    return BaseList<T>::m_content[BaseList<T>::m_begin];
  }

  void Queue<T>::copy_old_content(const T* old_content)
  {
    add_content(BaseList<T>::m_content, old_content + BaseList<T>::m_begin, BaseList<T>::m_size - BaseList<T>::m_begin);
    add_content(BaseList<T>::m_content, old_content, BaseList<T>::m_begin);
    BaseList<T>::m_begin = 0;
  }

}

#endif // DATASTRUCTURES_QUEUE_H
