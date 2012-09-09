#ifndef DATASTRUCTURES_BASELIST_H
#define DATASTRUCTURES_BASELIST_H

#include <cstddef>

namespace DataStructures {

  template <typename T>
  class BaseList
  {
  public:
    typedef size_t size_type;

    typedef ptrdiff_t difference_type;

    static const size_type DEFAULT_MIN_CAPACITY;

    typedef T value_type;

    typedef T& reference_type;

    typedef T* pointer_type;

    inline BaseList();

    explicit inline BaseList(size_type initial_size, const T& element = T());

    inline BaseList(const BaseList<T>& other);

    // inline BaseList(BaseList<T>&& other);

    inline virtual BaseList<T>& operator=(const BaseList<T>& other);

    // inline virtual BaseList<T>& operator=(BaseList<T>&& other);

    // This has to move the elements such that they are in subsequent order again.
    // This is important for resizing
    virtual void reorganize() = 0;

    template <typename Iterator>
    BaseList(Iterator begin, Iterator end);

    inline virtual ~BaseList();

    inline size_type size() const;

    inline bool empty() const;

    inline size_type min_capacity() const;

    inline void min_capacity(size_type min_capacity);

    inline size_type capacity() const;

    inline void reserve(size_type capacity);

    inline void shrinkable(bool shrinkable);

    inline bool shrinkable() const;

  private:
    static const size_type CAPACITY_DECREASE_FACTOR;

    T* m_content;

    size_type m_size;

    size_type m_capacity;

    size_type m_min_capacity;

    bool m_is_shrinkable;

  protected:
    inline void prepare_size(size_type new_size);

    inline T* data();

    inline const T* data() const;

    inline const T& at(size_type index) const;

    inline T& at(size_type index);

    inline void create(size_type index, const T& element);

    inline void replace(size_type index, const T& element);

    inline void destroy(size_type index);

    inline void destroy_part(size_type begin, size_type length);

    inline void add_content(const T * data, size_type insert_position, size_type length);

    inline void move(size_type target, size_type source);

    inline void move_part(size_type insert_position, size_type start, size_type length);

    inline void swap(size_type index1, size_type index2);

    inline void swap_parts(size_type start1, size_type start2, size_type length);

    inline void init_capacity(size_type initial_capacity);

    inline void adjust_capacity(size_type new_capacity);

  };

}

#include "baselist.hpp"

#endif // DATASTRUCTURES_BASELIST_H
