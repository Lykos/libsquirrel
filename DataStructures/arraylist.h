#ifndef DATASTRUCTURES_ARRAYLIST_H
#define DATASTRUCTURES_ARRAYLIST_H

#include "baselist.h"
#include "listiterator.h"

namespace DataStructures {

  template <typename T>
  class ArrayList;

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const ArrayList<T>& it);

  template <typename T>
  class ArrayList : public BaseList<T>
  {
    friend std::ostream& operator<< <> (std::ostream& out, const ArrayList<T>& it);
  public:
    typedef ListIterator<T, ArrayList<T> > iterator;

    typedef ListIterator<T const, ArrayList<T> const > const_iterator;

    typedef typename BaseList<T>::size_type size_type;

    inline ArrayList();

    inline explicit ArrayList(size_type initial_size, const T& element = T());

    /*template <typename Iterator>
    ArrayList(const Iterator& begin, const Iterator& end);*/

    template <typename Iterator>
    void push_all(const Iterator& begin, const Iterator& end);

    inline ArrayList<T> operator+(const ArrayList<T>& other) const;

    inline ArrayList<T>& operator+=(const ArrayList<T>& other);

    inline ArrayList<T> operator*(size_type factor) const;

    inline ArrayList<T>& operator*=(size_type factor);

    inline bool operator==(const ArrayList<T>& other) const;

    inline bool operator!=(const ArrayList<T>& other) const;

    inline const T& operator[](size_type i) const;

    inline T& operator[](size_type i);

    inline void push_back(const T& element);

    inline T pop_back();

    inline bool remove(const T& element);

    inline size_type remove_all(const T& element);

    inline void remove_position(size_type position);

    inline void remove_range(size_type start, size_type end);

    inline const T& front() const;

    inline T& front();

    inline const T& back() const;

    inline T& back();

    inline iterator begin();

    inline const_iterator begin() const;

    inline iterator end();

    inline const_iterator end() const;

    inline const T* data() const;

  };

}

#include "arraylist.hpp"

#endif // DATASTRUCTURES_ARRAYLIST_H
