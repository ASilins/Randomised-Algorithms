#include "TwoWiseMultiplyShiftHash.h"
#include "../../utils/NumberUtils.h"

TwoWiseMultiplyShiftHash::TwoWiseMultiplyShiftHash(const uint32_t r) : r(r)
{
    uint64_t m = std::numeric_limits<uint64_t>::max();
    a = NumberUtils::generate_random_uint(m);
    b = NumberUtils::generate_random_uint(m);

}

std::tuple<uint32_t, int32_t> TwoWiseMultiplyShiftHash::hash(const uint64_t &x) const
{
    uint64_t k = (a*x+b) >> 33;

    int64_t g_x = 2*(k & 1)-1;
    uint64_t h_x = (k >> 1) & (r-1);
    
    return std::make_tuple(h_x, g_x);
}
