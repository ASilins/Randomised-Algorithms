#include "HashingWithChaining.h"

HashingWithChaining::HashingWithChaining(const uint32_t m, const uint8_t w, const std::vector<uint32_t> &list)
: h(MultiplyShiftHash(w))
{
    table.resize(m);
    for (std::vector<uint32_t>& chain : table) {
        chain.reserve(5);
    }
    for (const uint32_t &x: list) {
        insert(x);
    }
}

void HashingWithChaining::insert(const uint32_t x) {
    table[h.hash(x)].push_back(x);
}

bool HashingWithChaining::query(const uint32_t x) {
    const uint32_t index = h.hash(x);
    if (index >= table.size()) return false;
    std::vector<uint32_t> &chain = table[index];
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


