#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "baselist.h"
#include "listiterator.h"
#include <initializer_list>

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

    inline Queue(std::initializer_list<T> list);

    inline explicit Queue(size_type initial_size = 0, const T& element = T());

    inline Queue(const Queue<T>& other);

    template <typename Iterator>
    inline Queue(const Iterator& begin, const Iterator& end);

    inline int_fast8_t compare_to(const Queue<T>& other) const;

    inline bool operator==(const Queue<T>& other) const;

    inline bool operator!=(const Queue<T>& other) const;

    inline bool operator<(const Queue<T>& other) const;

    inline bool operator<=(const Queue<T>& other) const;

    inline bool operator>(const Queue<T>& other) const;

    inline bool operator>=(const Queue<T>& other) const;

    template <typename Iterator>
    inline void assign(Iterator begin, Iterator end);

    inline void assign(size_type number, const T& element);

    inline iterator erase(iterator position);

    inline iterator erase(iterator start, iterator end);

    inline iterator erase(size_type index);

    inline iterator erase(size_type start, size_type end);

    inline iterator insert(size_type index, const T& element);

    inline void insert(size_type index, size_type number, const T& element);

    template <typename Iterator>
    inline void insert(size_type index, Iterator start, Iterator end);

    inline iterator insert(iterator position, const T& element);

    inline void insert(iterator position, size_type number, const T& element);

    template <typename Iterator>
    inline void insert(iterator position, Iterator start, Iterator end);

    inline void resize(size_type new_size, const T& element = T());

    inline const T& operator[](size_type i) const;

    inline T& operator[](size_type i);

    inline void clear();

    inline void push_back(const T& element);

    inline void push_front(const T& element);

    inline T pop_back();

    inline T pop_front();

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

    inline size_type q_index(size_type index) const;

    inline void destroy_queue_part(size_type q_start, size_type length);

    inline void move_queue_part(size_type q_insert_position, size_type q_start, size_type length);

    inline void make_room(size_type index, size_type old_length, size_type length);

    size_type m_begin = 0;

  };

}

#include "queue.hpp"

#endif // DATASTRUCTURES_QUEUE_H
