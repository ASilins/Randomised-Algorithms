#ifndef NUMBERUTILS_H
#define NUMBERUTILS_H

#include <algorithm>
#include <random>
#include <vector>

class NumberUtils {
public:
  static uint32_t generate_random_uint(uint32_t m);
  static uint64_t generate_random_uint(uint64_t m);
  static std::vector<uint64_t> generate_shuffled_list(uint32_t size);
  static std::vector<uint64_t> generate_list(uint64_t lower_bound, uint64_t upper_bound);
};

#endif //NUMBERUTILS_H
