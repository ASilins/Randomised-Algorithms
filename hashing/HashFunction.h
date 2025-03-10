#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
#include <iostream>
#include "../utils/NumberUtils.h"

class HashFunction {
public:
  HashFunction();
  explicit HashFunction( uint8_t w);
  [[nodiscard]] uint32_t hash( uint32_t x) const;

private:
  uint64_t a, b;
  uint8_t w;
};


#endif //HASHFUNCTION_H
