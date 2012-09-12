#include "field.h"

namespace LongArithmetic {

  template <typename T>
  inline T DivisionInverter<T>::operator()(const T& zero, const T& one, const T& element)
  {
    return one / element;
  }

  template <typename T>
  inline Field<T>::Field(const T& zero, const T& one, Inverter inverter):
    Ring<T>(zero, one),
    m_inverter (inverter)
  {}

  template <typename T>
  inline T Field<T>::mult_inv(const T& element) const
  {
    return m_inverter(zero, one, element);
  }
  
} // namespace LongArithmetic
