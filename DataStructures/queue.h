#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "baselist.h"
#include "listiterator.h"

namespace DataStructures {

  template <typename T>
  class Queue;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Queue<T>& it);

  template <typename T>
  class Queue : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const Queue<T>& it);
  public:
    typedef ListIterator<T, Queue<T> > iterator;

    typedef ListIterator<T const, Queue<T> const > const_iterator;

    typedef typename BaseList<T>::size_type size_type;

    typedef typename BaseList<T>::difference_type difference_type;

    inline Queue();

    inline Queue(const Queue<T>& other);

    template <typename Iterator>
    inline Queue(const Iterator& begin, const Iterator& end);

    inline bool operator==(const Queue<T>& other) const;

    inline bool operator!=(const Queue<T>& other) const { return !operator==(other); }

    template <typename Iterator>
    inline void push_all(const Iterator& begin, const Iterator& end);

    inline const T& operator[](size_type i) const;

    inline T& operator[](size_type i);

    inline void clear();

    inline void push(const T& element);

    inline T pop();

    inline const T& front() const;

    inline T& front();

    inline const T& back() const;

    inline T& back();

    inline iterator begin();

    inline const_iterator begin() const;

    inline iterator end();

    inline const_iterator end() const;

    inline void reorganize();

  private:

    inline size_type index_of(size_type index) const;

    size_type m_begin;

  };

}

#include "queue.hpp"

#endif // DATASTRUCTURES_QUEUE_H
