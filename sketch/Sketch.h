#ifndef SKETCH_H
#define SKETCH_H
#include <cstdint>

#include "../hashing/hash_functions/FourWiseIndependentHash.h"
#include "../hashing/hash_functions/TwoWiseMultiplyShiftHash.h"

class Sketch {
public:
    explicit Sketch(uint32_t r, bool use_multiply_shift = false);
    void update(const uint64_t &i, const uint64_t &delta);
    uint64_t query() const;
private:
    uint32_t r;
    bool use_multiply_shift;
    FourWiseIndependentHash h;
    TwoWiseMultiplyShiftHash h_two_wise;
    std::vector<uint64_t> table;
};

#endif //SKETCH_H
