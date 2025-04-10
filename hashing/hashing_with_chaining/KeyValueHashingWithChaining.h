#ifndef KEYVALUEHASHINGWITHCHAINING_H
#define KEYVALUEHASHINGWITHCHAINING_H
#include <tuple>
#include <vector>

#include "../hash_functions/MultiplyShiftHash.h"


class KeyValueHashingWithChaining {
public:
    explicit KeyValueHashingWithChaining(uint32_t m, uint8_t w);
    void update(const std::tuple<std::uint32_t, std::uint32_t> &key_value);
    uint64_t query() const;

private:
    std::vector<std::vector<std::tuple<std::uint32_t, std::uint32_t>>> table;
    MultiplyShiftHash h;
};



#endif //KEYVALUEHASHINGWITHCHAINING_H
