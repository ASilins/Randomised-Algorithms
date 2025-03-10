#ifndef PERFECTHASHING_H
#define PERFECTHASHING_H
#include "HashFunction.h"
#include "SecondaryArray.h"


class PerfectHashing {
public:
    explicit PerfectHashing(std::vector<uint32_t> &list, uint8_t w);
    bool query(uint32_t x) const;
    uint8_t getRehashes() const { return rehashes; }
    uint64_t getSecondaryRehashes() const { return secondaryRehashes; }
private:
    void insert(uint32_t x);
    void build(std::vector<uint32_t> &list);
    bool rehash(std::vector<uint32_t> &list);

    uint64_t n;
    uint8_t w;
    uint8_t rehashes;
    uint64_t secondaryRehashes;
    std::vector<SecondaryArray> table;
    HashFunction h;

};



#endif //PERFECTHASHING_H
