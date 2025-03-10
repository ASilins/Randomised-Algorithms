#include "PerfectHashing.h"

PerfectHashing::PerfectHashing(std::vector<uint32_t> &list, const uint8_t w) :
n(list.size()),
w(w),
rehashes(0),
secondaryRehashes(0),
table(std::vector<SecondaryArray>(2*n)),
// TODO: Nice comment here on why :)
h(HashFunction(w+1))
{
    build(list);
}

bool PerfectHashing::query(const uint32_t x) const {
    auto index = h.hash(x);
    if (index >= table.size()) return false;
    return table[index].query(x);
}


void PerfectHashing::insert(uint32_t x) {
    table[h.hash(x)].insert(x);
}

void PerfectHashing::build(std::vector<uint32_t> &list) {
    bool rehashNeeded = true;
    while (rehashNeeded) {
        rehashNeeded = rehash(list);
        ++rehashes;
        if (rehashNeeded) {
            h = HashFunction(w+1);
        }
    }

    for (int i = 0; i < table.size(); ++i) {
        secondaryRehashes += table[i].build();
    }
}

// TODO: There are some errors here currently...
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
        collisions -= table[index].collisions();
        table[index].insert(list[i]);
        collisions += table[index].collisions();
        // if there are more than n/2 collisions then we need to rehash
        if (collisions > n / 2) {
            std::cout << "Too many collisions! Rehashing main array" << std::endl;
            // resetting the table as we do not need the inner arrays anymore
            table = std::vector<SecondaryArray>(2*n);
            return true;
        }
    }
    return false;
}


