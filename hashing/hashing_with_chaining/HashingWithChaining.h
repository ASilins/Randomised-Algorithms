#ifndef HASHINGWITHCHAINING_H
#define HASHINGWITHCHAINING_H

#include <iostream>

#include "../hash_functions/MultiplyShiftHash.h"

class HashingWithChaining {
public:
    explicit HashingWithChaining(uint32_t m, uint8_t w, const std::vector<uint64_t> &list);
    bool query(uint64_t x);
    void print_table() const;
    uint32_t largest_linked_list() const;

private:
    void insert(uint64_t x);

    std::vector<std::vector<uint64_t>> table;
    MultiplyShiftHash h;
};

#endif //HASHINGWITHCHAINING_H
