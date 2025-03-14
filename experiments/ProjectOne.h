#ifndef PROJECTONE_H
#define PROJECTONE_H
#include <cstdint>
#include <vector>
#include "../utils/CSVWriter.h"


class ProjectOne {
public:
    static void run_experiments();
private:
    static void run_chaining_experiment(const CSVWriter &writer, const CSVWriter &list_writer, const std::vector<uint64_t> &list,
        const std::uint8_t &w, const std::uint32_t &m);

    static void run_red_black_experiment(const CSVWriter &writer, const std::vector<uint64_t> &list,  const uint32_t &m);

    static void run_perfect_hashing_experiment(const CSVWriter &writer, const CSVWriter &rehashes_writer, std::vector<uint64_t> &list,
        const uint8_t &w, const uint32_t &m);
};



#endif //PROJECTONE_H
