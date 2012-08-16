#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include "DataStructures_global.h"
#include "baselist.h"
#include "listiterator.h"
#include "listconstiterator.h"

namespace DataStructures {

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class DATASTRUCTURESSHARED_EXPORT Queue : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, Queue<T> > iterator;

    typedef ListConstIterator<T, Queue<T> > const_iterator;

    inline Queue();

    inline Queue(const Queue<T>& other);

    inline bool operator==(const Queue<T>& other) const;

    inline bool operator!=(const Queue<T>& other) const { return !operator==(other); }

    template <typename Begin, typename End>
    inline void push_all(const Begin& begin, const End& end);

    inline const T& operator[](index_type i) const { check_index(i); return BaseList<T>::m_content[(i + m_begin) % BaseList<T>::m_capacity]; }

    inline T& operator[](index_type i) { check_index(i); return BaseList<T>::m_content[(i + m_begin) % BaseList<T>::m_capacity]; }

    inline void clear();

    inline void push(const T& element);

    inline T pop();

    inline const T& front() const { check_empty(); return BaseList<T>::m_content[m_begin]; }

    inline T& front() { check_empty(); return BaseList<T>::m_content[m_begin]; }

    inline const T& back() const { check_empty(); return operator[](BaseList<T>::m_size - 1); }

    inline T& back() { check_empty(); return operator[](BaseList<T>::m_size - 1); }

    inline iterator begin() { return iterator(this, 0); }

    inline const_iterator begin() const { return const_iterator(this, 0); }

    inline iterator end() { return iterator(this, BaseList<T>::m_size); }

    inline const_iterator end() const { return const_iterator(this, BaseList<T>::m_size); }

    inline void reorganize();

  private:

    index_type m_begin;

  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Queue<T>& list)
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
  inline Queue<T>::Queue():
    BaseList<T>(),
    m_begin(0)
  {
  }

  template <typename T>
  inline Queue<T>::Queue(const Queue<T> &other):
    BaseList<T>(other),
    m_begin (other.m_begin)
  {
  }

  template <typename T>
  template <typename Begin, typename End>
  inline void Queue<T>::push_all(const Begin& begin, const End& end)
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
  inline bool Queue<T>::operator==(const Queue<T>& other) const
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
  inline void Queue<T>::clear()
  {
    index_type part_length = std::min(BaseList<T>::m_size, BaseList<T>::m_capacity - m_begin);
    BaseList<T>::destroy_segment(m_begin, part_length);
    BaseList<T>::destroy_segment(0, BaseList<T>::m_size - part_length);
    BaseList<T>::prepare_size(0);
  }

  template <typename T>
  inline void Queue<T>::push(const T& element)
  {
    index_type old_size = BaseList<T>::m_size;
    BaseList<T>::prepare_size(BaseList<T>::m_size + 1);
    operator[](old_size) = element;
  }

  template <typename T>
  inline T Queue<T>::pop()
  {
    check_empty();
    T element = BaseList<T>::m_content[m_begin];
    BaseList<T>::destroy(m_begin);
    ++m_begin;
    BaseList<T>::prepare_size(BaseList<T>::m_size - 1);
    return element;
  }

  template <typename T>
  inline void Queue<T>::reorganize()
  {
    const index_type capacity = BaseList<T>::m_capacity;
    index_type part_start = 0;
    index_type begin = m_begin;
    index_type size = BaseList<T>::m_size;
    index_type end = (begin + size) % capacity;
    while (part_start != capacity) {
      // invariants
      assert(part_start < capacity);
      assert(size <= BaseList<T>::m_size);
      assert(part_start <= begin && begin <= capacity);
      assert(part_start <= end && begin <= capacity);
      assert(begin <= end || (capacity - begin) + (end - part_start) == size);
      assert(begin >= end || end - begin == size);
      assert(begin != end || size == 0 || part_start + size == capacity);
      if (begin == end || begin == capacity || begin == part_start) {
        // #||# -> ## ||
        // 12|##| -> 12## ||
        // |12|## -> 12## ||
        break;
        /* Unecessary, but would be correct:
        part_start = capacity;
        begin = capacity;
        end = capacity;
        size = 0;*/
      } else if (end == part_start) {
        end = capacity;
      } else if (begin < end) {
        // ##|1234|# -> 1234### ||
        BaseList<T>::move_part(part_start, begin, size);
        part_start = capacity;
        /* Unnecessary, but would be correct:
        begin = capacity;
        end = capacity;
        size = 0;*/
      } else {
        index_type end_size = end - part_start;
        index_type begin_size = capacity - begin;
        assert(begin_size + end_size == size);
        if (end_size >= begin_size) {
          // 345|#|12 -> 12 5|#|34
          BaseList<T>::swap_parts(part_start, begin, begin_size);
          assert(begin_size > 0); // Necessary for progress
          part_start += begin_size;
          size = end_size;
          // begin, end remain unchanged
        } else if (begin - part_start <= begin_size) {
          index_type size_moved = begin - part_start;
          assert(size_moved >= end_size); // else the next step would be more efficient
          // 56|#|1234 -> 123 56|#|4
          BaseList<T>::swap_parts(part_start, begin, end_size);
          BaseList<T>::move_part(end, begin + end_size, begin - end);
          assert(end_size + (begin - end) == size_moved);
          size -= size_moved;
          part_start = begin;
          begin += size_moved;
          end += size_moved;
        } else if (end_size <= begin_size) {
          // 45|##|123 -> 123 #|45|#
          BaseList<T>::swap_parts(part_start, begin, end_size);
          BaseList<T>::move_part(end, begin + end_size, begin_size - end_size);
          part_start += begin_size;
          size = end_size;
          end += begin_size;
          // begin remains unchanged
        } else {
          assert(false);
        }
      }
    }
    m_begin = 0;
  }

}

#endif // DATASTRUCTURES_QUEUE_H
