#include "NumberUtils.h"

uint32_t NumberUtils::generate_random_uint(const uint32_t m)  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, m);

    return dist(gen);
}

uint64_t NumberUtils::generate_random_uint(const uint64_t m) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, m);

    return dist(gen);
}

 // Could be improved
std::vector<uint32_t> NumberUtils::generate_shuffled_list(uint32_t size) {
    std::vector<uint32_t> list(size);
    for (uint64_t i = 0; i < size; ++i) {
        list[i] = static_cast<uint32_t>((i*i)%size);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(list, gen);
    return list;
}