#ifndef DATASTRUCTURES_FIELD_H
#define DATASTRUCTURES_FIELD_H

#include "ring.h"

namespace DataStructures {
  
  template <typename T>
  struct DivisionInverter
  {
    T operator()(const T& zero, const T& one, const T& element);

  };

  template <typename T, typename Inverter = DivisionInverter<T> >
  class Field : public Ring<T>
  {
  public:
    inline Field(const T& zero, const T& one, Inverter inverter = Inverter());

    Field(const Field<T>& other) = delete;

    Field(Field<T>&& other) = delete;

    Field& operator=(const Field<T>& other) = delete;

    Field& operator=(Field<T>&& other) = delete;

    inline const T& modulus() const;

    inline bool operator==(const Field<T>& other) const;

    inline bool operator!=(const Field<T>& other) const;

    inline T mult_inv(const T& element) const;

  private:
    Inverter m_inverter;

  };
  
} // namespace DataStructures

#include "field.hpp"

#endif // DATASTRUCTURES_FIELD_H
