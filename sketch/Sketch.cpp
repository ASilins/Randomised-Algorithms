#include "Sketch.h"

/**
 * @brief Constructor for the Sketch class that initialises the hash function and the table using r.
 *
 * @param r The unsigned 8-bit integer that is used for hash function and to determine the size of the table by 2^r
 */
Sketch::Sketch(const uint8_t r) : h(FourWiseIndependentHash(r)), r(r) {
    table.resize(1ULL << r);
}

/**
 * @brief Updates the sketch table at h(i) by g(i) * delta.
 *
 * @param i The index to update
 * @param delta The delta value for the update
 */
void Sketch::update(const uint64_t &i, const uint64_t &delta) {
    auto [h_i, g_i] = h.hash(i);
    table[h_i] += g_i * delta;
}

/**
 * @brief Queries the sketch table by summing up the squares of the entries and returns the estimate.
 *
 * @return the estimate
 */
uint64_t Sketch::query() const {
    uint64_t results = 0;

    for (auto &entry : table) {
        results += entry * entry;
    }

    return results;
}
