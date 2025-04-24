#ifndef BINARYSEARCHHASH_H
#define BINARYSEARCHHASH_H
#include <cstdint>
#include <tuple>


class BinarySearchHash {
public:
    static uint64_t hash(uint64_t x_0, uint64_t x_1, uint64_t p);
private:
    static std::tuple<uint64_t, uint64_t> mul128(uint64_t a, uint64_t b);
};

#endif //BINARYSEARCHHASH_H
