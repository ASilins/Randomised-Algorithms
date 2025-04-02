#ifndef PERFECTHASHING_H
#define PERFECTHASHING_H
#include "../hash_functions/MultiplyShiftHash.h"
#include "SecondaryArray.h"


class PerfectHashing {
public:
    explicit PerfectHashing(std::vector<uint64_t> &list, uint8_t w);
    bool query(uint64_t x) const;
    uint8_t get_rehashes() const { return rehashes; }
    uint64_t get_secondary_rehashes() const { return secondary_rehashes; }
    uint64_t get_collisions() const { return collisions; }
    uint64_t get_buckets_hashed() const { return buckets_hashed; }
    void print_table() const;
private:
    void insert(uint64_t x);
    void build(std::vector<uint64_t> &list);
    bool rehash(std::vector<uint64_t> &list);

    uint64_t n;
    uint8_t w;
    uint8_t rehashes;
    uint64_t secondary_rehashes;
    uint64_t collisions;
    uint64_t buckets_hashed;
    std::vector<SecondaryArray> table;
    MultiplyShiftHash h;

};

#endif //PERFECTHASHING_H
