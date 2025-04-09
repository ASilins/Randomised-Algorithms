#include "NumberUtils.h"

#include <iostream>
#include <ostream>

/**
 * Generates a random unsigned 32-bit integer in the range [1, m].
 *
 * @param m Upper bound for the random number
 * @return Unsigned 32-bit integer in the range [1, m]
 */
uint32_t NumberUtils::generate_random_uint(const uint32_t m)  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(1, m);

    return dist(gen);
}

/**
 * Generates a random unsigned 64-bit integer in the range [1, m].
 *
 * @param m Upper bound for the random number
 * @return Unsigned 64-bit integer in the range [1, m]
 */
uint64_t NumberUtils::generate_random_uint(const uint64_t m) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(1, m);

    return dist(gen);
}

/**
 * Generates a shuffled list of numbers from 1 to size, where each number is squared.
 * The numbers in the list are unsigned 64-bit integers.
 *
 * @param size Size of the list to generate
 * @return A list of shuffled generated numbers
 */
std::vector<uint64_t> NumberUtils::generate_shuffled_list(uint32_t size) {
    std::vector<uint64_t> list(size);
    for (uint64_t i = 1; i <= size; ++i) {
        auto result = i*i;
        if (result > (1ULL >> 61) - 1) {
            std::cout << "Number is too large: " << result << std::endl;
            continue;
        }
        list[i-1] = i*i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(list, gen);
    return list;
}

/**
 * Generates a simple list of numbers in the range of [`lower_bound`, `upper_bound`].
 *
 * @param lower_bound Determines the smallest integer in the list
 * @param upper_bound Determines the largest integer in the list. Is used with `lower_bound` to determine the size of the list
 * @return A list of numbers from `lower_bound` to `upper_bound`
 */
std::vector<uint64_t> NumberUtils::generate_list(const uint64_t lower_bound, const uint64_t upper_bound) {
    std::vector<uint64_t> list(upper_bound - lower_bound);
    for (uint64_t i = lower_bound; i <= upper_bound; ++i) {
        list[i-lower_bound] = i;
    }
    return list;
}
