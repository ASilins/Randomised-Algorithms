#include "PerfectHashing.h"

PerfectHashing::PerfectHashing(std::vector<uint32_t> &list, const uint8_t w) :
n(list.size()),
w(w),
rehashes(0),
secondaryRehashes(0),
// If we set c = 1, then we can set the table size to be 2*n and the hash function is just w + 1 as n = 2^w.
table(std::vector<SecondaryArray>(2*n)),
h(MultiplyShiftHash(w+1))
{
    build(list);
}

bool PerfectHashing::query(const uint32_t x) const {
    auto index = h.hash(x);
    if (index >= table.size()) return false;
    return table[index].query(x);
}


void PerfectHashing::insert(uint32_t x) {
    std::cout << "Inserting " << h.hash(x) << std::endl;
    table[h.hash(x)].insert(x);
}

void PerfectHashing::build(std::vector<uint32_t> &list) {
    bool rehashNeeded = true;
    while (rehashNeeded) {
        rehashNeeded = rehash(list);
        ++rehashes;
        if (rehashNeeded) {
            h = MultiplyShiftHash(w+1);
        }
    }

    // TODO: This seems to be the bottleneck. It takes a long time to hash the secondary arrays with multiple collisions.
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].bucket.size() <= 1) continue;
        secondaryRehashes += table[i].build();
    }
    std::cout << "Secondary rehashes: " << secondaryRehashes << std::endl;
}

bool PerfectHashing::rehash(std::vector<uint32_t> &list) {
    auto collisions = 0;
    for (int i = 0; i < list.size(); ++i) {
        const auto index = h.hash(list[i]);
        if (index >= table.size()) {
            std::cerr << "Hash index out of bounds: " << index << std::endl;
            return true; // Trigger a rehash if the index is out of bounds
        }
        // We want to remove the collision count in that bucket from the total collisions so that it can change
        // correctly after inserting the new element in the bucket.
        auto& bucket = table[index];
        collisions -= bucket.collisions();
        bucket.insert(list[i]);
        collisions += bucket.collisions();
        // if there are more than n/2 collisions then we need to rehash
        if (collisions > n / 2) {
            std::cout << collisions << std::endl;
            std::cout << "Too many collisions! Rehashing main array" << std::endl;
            // resetting the table as we do not need the inner arrays anymore
            table = std::vector<SecondaryArray>(2*n);
            return true;
        }
    }
    return false;
}


