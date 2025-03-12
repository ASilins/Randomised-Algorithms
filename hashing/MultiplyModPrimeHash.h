#ifndef MULTIPLYMODPRIMEHASH_H
#define MULTIPLYMODPRIMEHASH_H
#include <cstdint>


class MultiplyModPrimeHash {
public:
    MultiplyModPrimeHash();
    explicit MultiplyModPrimeHash(uint32_t m);
    [[nodiscard]] uint32_t hash(uint64_t x) const;
private:
    uint32_t m;
    uint64_t a, b, prime;
};

#endif //MULTIPLYMODPRIMEHASH_H
