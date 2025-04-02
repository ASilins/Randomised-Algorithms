#ifndef MULTIPLYMODPRIMEHASH_H
#define MULTIPLYMODPRIMEHASH_H
#include <cstdint>


class MultiplyModPrimeHash {
public:
    MultiplyModPrimeHash();
    explicit MultiplyModPrimeHash(uint32_t m);
    uint32_t hash(uint64_t x) const;
    void scramble(uint32_t m);
private:
    uint32_t m;
    uint64_t a, b;
    // Mersenne's prime
    const uint64_t prime = (1ULL << 61) - 1;
};

#endif //MULTIPLYMODPRIMEHASH_H
