#ifndef MODPRIMEFOR128BITHASH_H
#define MODPRIMEFOR128BITHASH_H
#include <cstdint>


class ModPrimeFor128BitHash {
public:
    [[nodiscard]] uint64_t hash(uint64_t x_0, uint64_t x_1) const;
private:
    // Mersenne's prime of 2^61 - 1
    uint64_t p = (1ULL << 61) - 1;
};



#endif //MODPRIMEFOR128BITHASH_H
