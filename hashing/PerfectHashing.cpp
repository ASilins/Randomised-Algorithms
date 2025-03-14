#include "PerfectHashing.h"

PerfectHashing::PerfectHashing(std::vector<uint64_t> &list, const uint8_t w) :
n(list.size()),
w(w),
rehashes(0),
secondary_rehashes(0),
collisions(0),
buckets_hashed(0),
// If we set c = 1, then we can set the table size to be 2*n and the hash function is just w + 1 as n = 2^w.
table(std::vector<SecondaryArray>(2*n)),
h(MultiplyShiftHash(w+1))
{
    build(list);
}

bool PerfectHashing::query(const uint64_t x) const {
    auto index = h.hash(x);
    if (index >= table.size()) return false;
    return table[index].query(x);
}

void PerfectHashing::print_table() const {
    for (int i = 0; i < table.size(); ++i) {
        std::cout << "Index: " << i;
        table[i].printTable();
        std::cout << std::endl;
    }
}

void PerfectHashing::insert(uint64_t x) {
    std::cout << "Inserting " << h.hash(x) << std::endl;
    table[h.hash(x)].insert(x);
}

void PerfectHashing::build(std::vector<uint64_t> &list) {
    bool rehashNeeded = true;
    while (rehashNeeded) {
        rehashNeeded = rehash(list);
        ++rehashes;
        if (rehashNeeded) {
            this->h.scramble();
        }
    }

    for (uint64_t i = 0; i < table.size(); ++i) {
        auto hash_count = table[i].build();
        if (hash_count > 0) {
            secondary_rehashes += hash_count;
            buckets_hashed++;
        }
    }
}

bool PerfectHashing::rehash(std::vector<uint64_t> &list) {
    for (uint64_t i = 0; i < list.size(); ++i) {
        const auto index = h.hash(list[i]);
        // We want to remove the collision count in that bucket from the total collisions so that it can change
        // correctly after inserting the new element in the bucket.
        auto& bucket = table[index];
        this->collisions -= bucket.collisions();
        bucket.insert(list[i]);
        this->collisions += bucket.collisions();
        // if there are more than n/2 collisions then we need to rehash
        if (this->collisions > n / 2) {
            std::cout << this->collisions << std::endl;
            std::cout << "Too many collisions! Rehashing main array" << std::endl;
            // resetting the table as we do not need the inner arrays anymore
            table = std::vector<SecondaryArray>(2*n);
            this->collisions = 0;
            return true;
        }
    }
    return false;
}


