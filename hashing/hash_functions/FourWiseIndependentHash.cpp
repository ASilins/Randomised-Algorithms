#include "FourwiseIndependentHash.h"
#include "../../utils/NumberUtils.h"

FourwiseIndependentHash::FourwiseIndependentHash(uint32_t r) : r(r)
{
    a = NumberUtils::generate_random_uint(p-1);
    b = NumberUtils::generate_random_uint(p-1);
    c = NumberUtils::generate_random_uint(p-1);
    d = NumberUtils::generate_random_uint(p-1);
}

std::tuple<uint32_t, uint32_t> FourwiseIndependentHash::hash(uint64_t x) const
{
    uint32_t k = (a*x+b) % p;
    k = (k*x+c) % p;
    k = (k*x+d) % p;

    uint32_t g_x = 2*(k & 1)-1;
    uint32_t h_x = (k >> 1) & (r-1);
    
    return std::make_tuple(g_x, h_x);
}
