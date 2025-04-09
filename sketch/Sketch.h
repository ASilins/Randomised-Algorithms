#ifndef SKETCH_H
#define SKETCH_H
#include <cstdint>

#include "../hashing/hash_functions/FourWiseIndependentHash.h"

class Sketch {
public:
    explicit Sketch(uint8_t r);
    void update(uint64_t i, uint64_t delta);
    uint64_t query() const;
private:
    std::vector<uint64_t> table;
    FourWiseIndependentHash h;
    uint8_t r;
};

#endif //SKETCH_H
