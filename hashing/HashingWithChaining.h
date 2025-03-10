#ifndef HASHINGWITHCHAINING_H
#define HASHINGWITHCHAINING_H

#include <iostream>
#include "HashFunction.h"

class HashingWithChaining {
public:
    explicit HashingWithChaining(uint32_t m, uint8_t w);
    void insert(uint32_t x);
    bool query(uint32_t x);
    void print_table() const;

private:
    std::vector<std::vector<uint32_t>> table;
    HashFunction h;
};

#endif //HASHINGWITHCHAINING_H
