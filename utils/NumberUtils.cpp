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

std::vector<uint32_t> NumberUtils::generate_shuffled_list(uint32_t size) {
    std::vector<uint32_t> list(size);
    std::vector used(UINT32_MAX, false);
    uint64_t count = 0;
    for (uint64_t i = 0; count < size; ++i) {
        uint32_t key = generate_random_uint(UINT32_MAX);
        if (!used[key]) {
            list[count++] = key;
            used[key] = true;
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(list, gen);
    return list;
}