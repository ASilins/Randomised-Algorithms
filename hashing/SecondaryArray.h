#ifndef SECONDARYARRAY_H
#define SECONDARYARRAY_H
#include <vector>


#include "MultiplyModPrimeHash.h"

class SecondaryArray {
public:
    std::vector<uint32_t> bucket;

    explicit SecondaryArray();
    void insert(uint32_t x);
    bool query(uint32_t x) const;
    uint8_t build();
    uint32_t collisions() const;

private:
    bool rehash();

    MultiplyModPrimeHash h;
};

#endif //SECONDARYARRAY_H
