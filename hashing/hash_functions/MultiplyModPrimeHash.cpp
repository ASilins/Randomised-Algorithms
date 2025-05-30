#include "MultiplyModPrimeHash.h"

#include <iostream>

#include "../../utils/NumberUtils.h"

MultiplyModPrimeHash::MultiplyModPrimeHash() : m(0), a(0), b(0) {}

MultiplyModPrimeHash::MultiplyModPrimeHash(uint32_t m) : m(m) {
    a = NumberUtils::generate_random_uint(prime-1);
    b = NumberUtils::generate_random_uint(prime-1);
}

uint32_t MultiplyModPrimeHash::hash(uint64_t x) const {
    __uint128_t result = static_cast<__uint128_t>(a) * x + b;
    result = (result & prime) + (result >> 61);
    if (result >= prime) result -= prime;
    return static_cast<uint32_t>(result % m);
}

void MultiplyModPrimeHash::scramble(uint32_t m) {
    this->m = m;
    a = NumberUtils::generate_random_uint(prime-1);
    b = NumberUtils::generate_random_uint(prime-1);
}

