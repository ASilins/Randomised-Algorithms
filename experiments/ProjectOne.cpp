#include "ProjectOne.h"
#include <iostream>

#include "../hashing/hashing_with_chaining/HashingWithChaining.h"
#include "../hashing/perfect_hashing/PerfectHashing.h"
#include "../hashing/red_black_tree/RedBlackSearchTree.h"
#include "../utils/NumberUtils.h"
#include "../utils/TimerUtils.h"


void ProjectOne::run_experiments() {
    CSVWriter time_writer("../analysis/ProjectOne/results.csv", "algorithm,n,build,query");
    CSVWriter linked_list_writer("../analysis/ProjectOne/linked_list.csv", "n,count");
    CSVWriter rehashes_writer("../analysis/ProjectOne/rehashes.csv", "n,hashes,secondary_rehashes");

    TimerUtils::time_experiment_with_print("Starting experiment one!", [&time_writer, &linked_list_writer, &rehashes_writer]() {
        for (uint8_t i = 5; i <= 24; ++i)
        {
            std::cout << "Running for 2^" << static_cast<int>(i) << ":" << std::endl;
            const uint32_t m = 1ULL<<i;
            for (uint8_t j = 0; j < 5; ++j)
            {
                std::cout << "Executing iteration " << static_cast<int>(j) + 1 << std::endl;
                auto [build_time, number_list] =
                    TimerUtils::time_experiment_with_result<std::vector<uint64_t>>([&m]() {
                        return NumberUtils::generate_shuffled_list(m);
                    });
                std::cout << "List build time: " << build_time << " ms" << std::endl;

                run_red_black_experiment(time_writer, number_list, m);
                run_chaining_experiment(time_writer, linked_list_writer, number_list, i, m);
                run_perfect_hashing_experiment(time_writer, rehashes_writer, number_list, i, m);
            }
            std::cout << std::endl;
        }
    });
}

void ProjectOne::run_chaining_experiment(const CSVWriter &writer, const CSVWriter &list_writer, const std::vector<uint64_t> &list,
    const uint8_t &w, const uint32_t &m)
{
    // build time
    auto [build_time, hashing_with_chaining] = TimerUtils::time_experiment_with_result<HashingWithChaining>([&m, &w, &list]() {
        return HashingWithChaining(m, w, list);
    });

    // query time
    auto query_time = TimerUtils::time_experiment([&hashing_with_chaining, &m, &list]() {
        for (uint64_t i = 0; i < m; i++) {
            hashing_with_chaining.query(list.at(i));
        }
    });

    // results
    writer.append_row("HashingWithChaining", std::to_string(m), std::to_string(build_time), std::to_string(query_time));
    list_writer.append_row(std::to_string(m), std::to_string(hashing_with_chaining.largest_linked_list()));
}

void ProjectOne::run_red_black_experiment(const CSVWriter &writer, const std::vector<uint64_t> &list,  const uint32_t &m)
{
    // build time
    auto [build_time, red_black_search_tree] = TimerUtils::time_experiment_with_result<RedBlackSearchTree>([&list]() {
        return RedBlackSearchTree(list);
    });

    // query time
    auto query_time = TimerUtils::time_experiment([&red_black_search_tree, &m, &list]() {
        for (uint64_t i = 0; i < m; i++) {
            (void)red_black_search_tree.query(list.at(i));
        }
    });

    // results
    writer.append_row("RedBlackSearchTree", std::to_string(m), std::to_string(build_time), std::to_string(query_time));
}

void ProjectOne::run_perfect_hashing_experiment(const CSVWriter &writer, const CSVWriter &rehashes_writer, std::vector<uint64_t> &list, const uint8_t &w, const uint32_t &m)
{
    // build time
    auto [build_time, perfect_hashing] = TimerUtils::time_experiment_with_result<PerfectHashing>([&list, &w]() {
        return PerfectHashing(list, w);
    });

    // query time
    auto query_time = TimerUtils::time_experiment([&perfect_hashing, &m, &list]() {
        for (uint64_t i = 0; i < m; i++) {
        perfect_hashing.query(list.at(i));
        }
    });

    // results
    writer.append_row("PerfectHashing", std::to_string(m), std::to_string(build_time), std::to_string(query_time));
    rehashes_writer.append_row(std::to_string(m), std::to_string(perfect_hashing.get_rehashes()), std::to_string(perfect_hashing.get_secondary_rehashes()));
}