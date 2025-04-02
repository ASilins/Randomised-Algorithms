#include "KeyValueHashingWithChaining.h"

KeyValueHashingWithChaining::KeyValueHashingWithChaining(uint32_t m, uint8_t w) : h(MultiplyShiftHash(w))
{
    table.resize(m);
}

void KeyValueHashingWithChaining::update(std::tuple<std::uint32_t, std::uint32_t> key_value) {
    const uint32_t index = h.hash(static_cast<uint64_t>(std::get<0>(key_value)));
    auto &chain = table[index];
    for (auto & entry : chain) {
        if (std::get<0>(entry) == std::get<0>(key_value)) {
            std::get<1>(entry) = std::get<1>(entry) + std::get<1>(key_value);
            return;
        }
    }
    // append to the chain if the key does not exist
    chain.push_back(key_value);
}

uint64_t KeyValueHashingWithChaining::query() const {
    uint64_t result = 0;
    for (const auto &chain : table) {
        for (const auto &entry : chain) {
            result += std::get<1>(entry) * std::get<1>(entry);
        }
    }
    return result;
}

