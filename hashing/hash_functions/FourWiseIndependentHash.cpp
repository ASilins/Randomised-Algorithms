#include "FourWiseIndependentHash.h"
#include "../../utils/NumberUtils.h"

FourWiseIndependentHash::FourWiseIndependentHash(const uint32_t r) : r(r)
{
    a = NumberUtils::generate_random_uint(p-1);
    b = NumberUtils::generate_random_uint(p-1);
    c = NumberUtils::generate_random_uint(p-1);
    d = NumberUtils::generate_random_uint(p-1);
}

std::tuple<uint32_t, int32_t> FourWiseIndependentHash::hash(const uint64_t &x) const
{
    uint64_t k = (a*x+b) % p;
    k = (k*x+c) % p;
    k = (k*x+d) % p;

    int64_t g_x = 2*(k & 1)-1;
    uint64_t h_x = (k >> 1) & (r-1);
    
    return std::make_tuple(h_x, g_x);
}
