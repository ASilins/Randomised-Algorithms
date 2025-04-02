#ifndef FOURWISEINDEPENDENTHASH_H
#define FOURWISEINDEPENDENTHASH_H
#include <iostream>

class FourwiseIndependentHash {
public:
    FourwiseIndependentHash(uint32_t r);
    std::tuple<uint32_t, uint32_t> hash(uint64_t x) const;
private:
    uint64_t a, b, c, d;
    uint32_t r;
    // Mersenne's prime 2^31-1
    const uint32_t p = (1ULL << 31) - 1;
};


#endif
