#include "SecondaryArray.h"

#include <iostream>

SecondaryArray::SecondaryArray() : h(MultiplyModPrimeHash()) {
}

void SecondaryArray::insert(const uint64_t x) {
    bucket.push_back(x);
}

bool SecondaryArray::query(const uint64_t x) const {
    auto index = h.hash(x);
    auto result = bucket[index] == x;
    if (!result) {
        std::cout << "Entry could not be found: " << x << " at index: " << index << std::endl;
    }
    return result;
}

/**
 * Build the secondary array by calling rehash for the array. It rehashed the array until there are no collisions.
 *
 * @return the number of rehashed until no collisions
 */
uint8_t SecondaryArray::build() {
    uint8_t rehash_count = 0;
    if (bucket.size() <= 1) {
        h.scramble(bucket.size());
        return 0;
    }
    bool rehash_needed = true;
    while (rehash_needed) {
        rehash_needed = rehash();
        ++rehash_count;
    }
    // We want to return the number of rehashes. We know that if it is 1 then it was built on the first hash
    return rehash_count - 1;
}

uint32_t SecondaryArray::collisions() const {
    const uint32_t n = static_cast<uint32_t>(bucket.size());
    return (n * n - n) / 2;
}

void SecondaryArray::printTable() const {
    for (uint64_t i = 0; i < bucket.size(); ++i) {
        std::cout << " " << bucket[i];
    }
}

/**
 * Rehash the secondary array by creating new hash function, new bucket, iterating over the bucket and
 * if there are no collisions then setting the new bucket to the bucket. If there is a collision then
 * the bucket does not change
 *
 * @return true if there was a collision
 */
bool SecondaryArray::rehash() {
    auto q = bucket.size() * bucket.size();
    std::vector<uint64_t> newBucket(q, 0);
    this->h.scramble(q);
    for (uint64_t i = 0; i < bucket.size(); ++i) {
        auto index = h.hash(bucket[i]);
        // if there is a collision then we need to rehash
        if (newBucket[index] != 0) {
            return true;
        }
        newBucket[index] = bucket[i];
    }
    bucket = newBucket;
    return false;
}
