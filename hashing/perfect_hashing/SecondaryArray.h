#ifndef SECONDARYARRAY_H
#define SECONDARYARRAY_H
#include <vector>

#include "../hash_functions/MultiplyModPrimeHash.h"

class SecondaryArray {
public:
    std::vector<uint64_t> bucket;

    explicit SecondaryArray();
    void insert(uint64_t x);
    bool query(uint64_t x) const;
    uint8_t build();
    uint32_t collisions() const;
    void printTable() const;

private:
    bool rehash();

    MultiplyModPrimeHash h;
};

#endif //SECONDARYARRAY_H
