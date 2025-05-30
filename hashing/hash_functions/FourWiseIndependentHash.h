#ifndef FOURWISEINDEPENDENTHASH_H
#define FOURWISEINDEPENDENTHASH_H
#include <iostream>
#include <cstdint>
#include <vector>

class FourWiseIndependentHash {
public:
    FourWiseIndependentHash(uint32_t r);
    std::tuple<uint32_t, int32_t> hash(const uint64_t &x) const;
private:
    uint64_t a, b, c, d;
    uint32_t r;
    // Mersenne's prime 2^31-1
    const uint32_t p = (1ULL << 31) - 1;
};


#endif
