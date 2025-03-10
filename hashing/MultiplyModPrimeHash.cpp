#include "MultiplyModPrimeHash.h"

#include <iostream>

#include "../utils/NumberUtils.h"

MultiplyModPrimeHash::MultiplyModPrimeHash() : a(0), b(0), m(0), prime(0) {}

MultiplyModPrimeHash::MultiplyModPrimeHash(uint32_t m) : m(m) {
    // Mersenne's prime
    prime = (1ULL << 61) - 1;
    a = NumberUtils::generate_random_uint(prime-1);
    b = NumberUtils::generate_random_uint(prime-1);
}

uint32_t MultiplyModPrimeHash::hash(uint32_t x) const {
    // Perform the multiplication, addition, modulo operation using __uint128_t
    __uint128_t result = static_cast<__uint128_t>(a) * x + b;  // (a * x + b)
    result = result % prime;  // Modulo prime
    result = result % m;      // Modulo m
    return static_cast<uint32_t>(result);
}


