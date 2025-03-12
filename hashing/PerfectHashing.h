#ifndef PERFECTHASHING_H
#define PERFECTHASHING_H
#include "MultiplyShiftHash.h"
#include "SecondaryArray.h"


class PerfectHashing {
public:
    explicit PerfectHashing(std::vector<uint64_t> &list, uint8_t w);
    bool query(uint32_t x) const;
    uint8_t get_rehashes() const { return rehashes; }
    uint64_t get_secondary_rehashes() const { return secondaryRehashes; }
    void print_table() const;
private:
    void insert(uint64_t x);
    void build(std::vector<uint64_t> &list);
    bool rehash(std::vector<uint64_t> &list);

    uint64_t n;
    uint8_t w;
    uint8_t rehashes;
    uint64_t secondaryRehashes;
    std::vector<SecondaryArray> table;
    MultiplyShiftHash h;

};



#endif //PERFECTHASHING_H
