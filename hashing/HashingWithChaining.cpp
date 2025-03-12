#include "HashingWithChaining.h"

HashingWithChaining::HashingWithChaining(const uint32_t m, const uint8_t w, const std::vector<uint64_t> &list)
: h(MultiplyShiftHash(w))
{
    table.resize(m);
    for (std::vector<uint64_t>& chain : table) {
        chain.reserve(5);
    }
    for (const uint32_t &x: list) {
        insert(x);
    }
}

void HashingWithChaining::insert(const uint64_t x) {
    table[h.hash(x)].push_back(x);
}

bool HashingWithChaining::query(const uint64_t x) {
    const uint32_t index = h.hash(x);
    if (index >= table.size()) return false;
    std::vector<uint64_t> &chain = table[index];
    return std::ranges::find(chain, x) != chain.end();
}

void HashingWithChaining::print_table() const {
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "Index " << i << ": ";
        for (const unsigned &val: table[i]) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

uint32_t HashingWithChaining::largest_linked_list() const {
    uint32_t largest = 0;
    for (uint32_t i = 0; i < table.size(); ++i) {
        if (table[i].size() > largest) {
            largest = table[i].size();
        }
    }
    return largest;
}



