#include "ModPrimeFor128BitHash.h"

uint64_t ModPrimeFor128BitHash::hash(const uint64_t x_0, const uint64_t x_1) const {
    uint64_t result = (x_0 << 3 | x_1 >> 61) + (x_1 & p);
    if (result >= p)
        result -= p;
    return result;
}