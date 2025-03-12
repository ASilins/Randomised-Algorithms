#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
#include <iostream>
#include "../utils/NumberUtils.h"

class MultiplyShiftHash {
public:
  MultiplyShiftHash();
  explicit MultiplyShiftHash(uint8_t w);
  [[nodiscard]] uint32_t hash(uint64_t x) const;

private:
  uint64_t a;
  uint8_t w;
};


#endif //HASHFUNCTION_H
