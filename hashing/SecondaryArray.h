#ifndef SECONDARYARRAY_H
#define SECONDARYARRAY_H
#include "HashFunction.h"


class SecondaryArray {
public:
    explicit SecondaryArray();
    void insert(uint32_t x);
    bool query(uint32_t x) const;
    uint8_t build();
    uint32_t collisions() const;

private:
    bool rehash();

    HashFunction h;
    std::vector<uint32_t> bucket;
};



#endif //SECONDARYARRAY_H
