#include "MultiplyShiftHash.h"

MultiplyShiftHash::MultiplyShiftHash() {
    w = 0;
    a = 0;
    b = 0;
}

MultiplyShiftHash::MultiplyShiftHash(const uint8_t w) : w(w) {
    do {
        a = NumberUtils::generate_random_uint(UINT64_MAX);
        b = NumberUtils::generate_random_uint(UINT64_MAX);
    } while (a == b);
}

uint32_t MultiplyShiftHash::hash(const uint32_t x) const {
    return static_cast<uint32_t>((a*x + b) >> (64-w));
}