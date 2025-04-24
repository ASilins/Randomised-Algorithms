#include "BinarySearchHash.h"

#include <iomanip>
#include <iostream>

uint64_t BinarySearchHash::hash(uint64_t x_0, uint64_t x_1, uint64_t p) {
    uint64_t r_low = 0;
    uint64_t r_high = 1ULL << 61;
    uint64_t best_r = 0;

    while (r_low <= r_high) {
        uint64_t r_mid = r_low + (r_high - r_low) / 2;
        auto [prod_high, prod_low] = mul128(p, r_mid);

        if (prod_high < x_0 || (prod_high == x_0 && prod_low <= x_1)) {
            best_r = r_mid;
            r_low = r_mid + 1;
        } else {
            r_high = r_mid - 1;
        }
    }

    auto [rp_high, rp_low] = mul128(p, best_r);

    // based on the fact that p is less than 2^61 which would fit in 64 bits, and that we find r
    // that allows us to get the remainder of the x mod p, then it is safe to assume that we only need
    // to do substraction on the least significant bits
    return x_1 - rp_low;
}

std::tuple<uint64_t, uint64_t> BinarySearchHash::mul128(uint64_t a, uint64_t b) {
    uint64_t a_lo = static_cast<uint32_t>(a);
    uint64_t a_hi = a >> 32;
    uint64_t b_lo = static_cast<uint32_t>(b);
    uint64_t b_hi = b >> 32;

    uint64_t lo_lo = a_lo * b_lo;
    uint64_t hi_lo = a_hi * b_lo;
    uint64_t lo_hi = a_lo * b_hi;
    uint64_t hi_hi = a_hi * b_hi;

    uint64_t mid = (lo_lo >> 32) + (hi_lo & 0xFFFFFFFF) + (lo_hi & 0xFFFFFFFF);
    uint64_t low = (mid << 32) | (lo_lo & 0xFFFFFFFF);
    uint64_t high = hi_hi + (hi_lo >> 32) + (lo_hi >> 32) + (mid >> 32);

    return {high, low};
}
