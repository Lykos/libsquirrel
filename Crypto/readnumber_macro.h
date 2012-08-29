#ifndef READNUMBER_MACRO_H
#define READNUMBER_MACRO_H

#define READ_NUMBER(errll, errl, var, raw) \
  number_t var;\
{ \
  PREC(errll, length >= length_length); \
  number_size_t var_length = read_length(raw); \
  raw += length_length; \
  length -= length_length; \
  PREC(errl, length >= var_length); \
  var = m_converter.read_number(raw, var_length); \
  raw += var_length; \
  length -= var_length; \
}
#endif // READNUMBER_MACRO_H
