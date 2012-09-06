#ifndef READNUMBER_MACRO_H
#define READNUMBER_MACRO_H

#define INIT_READ(raw) \
  number_size_t pos = 0; \
  number_size_t length = raw.length();

#define READ_NUMBER(errll, errl, var, raw) \
  number_t var;\
{ \
  PREC(errll, length >= length_length); \
  number_size_t var_length = read_length(raw.substr(pos, length_length)); \
  pos += length_length; \
  length -= length_length; \
  PREC(errl, length >= var_length); \
  var = m_converter.binread(raw.substr(pos, var_length)); \
  pos += var_length; \
  length -= var_length; \
}
#endif // READNUMBER_MACRO_H
