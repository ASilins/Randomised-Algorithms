#include "MultiplyShiftHash.h"

MultiplyShiftHash::MultiplyShiftHash() {
    w = 0;
    a = 0;
}

MultiplyShiftHash::MultiplyShiftHash(const uint8_t w) : w(w) {
    do {
        a = NumberUtils::generate_random_uint(UINT64_MAX);
    } while (a % 2 == 0);
}

uint32_t MultiplyShiftHash::hash(const uint64_t x) const {
    return static_cast<uint32_t>(static_cast<uint64_t>(a*x) >> (64-w));
}

void MultiplyShiftHash::scramble() {
    do {
        a = NumberUtils::generate_random_uint(UINT64_MAX);
    } while (a % 2 == 0);
}
