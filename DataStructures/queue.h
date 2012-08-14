#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "DataStructures_global.h"
#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"

namespace DataStructures {

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Queue : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, Queue<T> > iterator;

    typedef ListConstIterator<T, Queue<T> > const_iterator;

    Queue();

    Queue(const Queue<T>& other);

    bool operator==(const Queue<T>& other) const;

    bool operator!=(const Queue<T>& other) const { return !operator==(other); }

    template <typename Begin, typename End>
    void push_all(const Begin& begin, const End& end);

    inline const T& operator[](index_type i) const { check_index(i); return BaseList<T>::m_content[(i + m_begin) % BaseList<T>::m_capacity]; }

    inline T& operator[](index_type i) { check_index(i); return BaseList<T>::m_content[(i + m_begin) % BaseList<T>::m_capacity]; }

    void push(const T& element);

    T pop();

    const T& top() const { check_empty(); return BaseList<T>::m_content[m_begin]; }

    T& top() { check_empty(); return BaseList<T>::m_content[m_begin]; }

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::m_size); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::m_size); }

  protected:
    void copy_old_content(const T *old_content);

  private:

    index_type m_begin;

  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Queue<T>& list)
  {
    out << "Queue[";
    for (typename Queue<T>::const_iterator it = list.begin(); it != list.end(); it++) {
      out << *it;
      if (it + 1 != list.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  template <typename T>
  Queue<T>::Queue():
    BaseList<T>(),
    m_begin(0)
  {
  }

  template <typename T>
  Queue<T>::Queue(const Queue<T> &other):
    BaseList<T>(other),
    m_begin (other.m_begin)
  {
  }

  template <typename T>
  template <typename Begin, typename End>
  void Queue<T>::push_all(const Begin& begin, const End& end)
  {
    if (end <= begin) {
      return;
    }
    index_type i = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + (end - begin));
    for (Begin it = begin; it != end; ++it, ++i) {
      operator[](i) = *it;
    }
  }

  template <typename T>
  bool Queue<T>::operator==(const Queue<T>& other) const
  {
    if (BaseList<T>::size() != other.size()) {
      return false;
    }
    for (index_type i = 0; i < BaseList<T>::size(); ++i) {
      if (operator[](i) != other.operator[](i)) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  void Queue<T>::push(const T& element)
  {
    index_type old_size = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + 1);
    operator[](old_size) = element;
  }

  template <typename T>
  T Queue<T>::pop()
  {
    check_empty();
    T element = BaseList<T>::m_content[m_begin++];
    BaseList<T>::prepare_size(BaseList<T>::m_size - 1);
    return element;
  }

  template <typename T>
  void Queue<T>::copy_old_content(const T* old_content)
  {
    BaseList<T>::add_content(old_content + m_begin, 0, BaseList<T>::m_size - m_begin);
    BaseList<T>::add_content(old_content, BaseList<T>::m_size - m_begin, m_begin);
    m_begin = 0;
  }

}

#endif // DATASTRUCTURES_QUEUE_H
