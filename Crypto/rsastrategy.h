#ifndef RSASTRATEGY_H
#define RSASTRATEGY_H

class RSAStrategy
{
public:
  RSAStrategy();

  virtual RSAKey::number_t encrypt() const = 0;

  virtual RSAKey::number_t decrypt() const = 0;
};

#endif // RSASTRATEGY_H
