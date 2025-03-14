#include "ProjectOne.h"
#include <chrono>

#include "../hashing/HashingWithChaining.h"
#include "../hashing/RedBlackSearchTree.h"
#include "../hashing/PerfectHashing.h"

void ProjectOne::run_experiments() {
    CSVWriter time_writer("../analysis/results.csv", "algorithm,n,build,query");
    CSVWriter linked_list_writer("../analysis/linked_list.csv", "n,count");
    CSVWriter rehashes_writer("../analysis/rehashes.csv", "n,hashes,secondary_rehashes");

    std::cout << "Starting experiment one!" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (uint8_t i = 5; i <= 24; ++i)
    {
        std::cout << "Running for 2^" << static_cast<int>(i) << ":" << std::endl;
        const uint32_t m = 1ULL<<i;
        for (uint8_t j = 0; j < 5; ++j)
        {
            std::cout << "Executing iteration " << static_cast<int>(j) + 1 << std::endl;
            auto build_start = std::chrono::high_resolution_clock::now();
            std::vector<uint64_t> number_list = NumberUtils::generate_shuffled_list(m);
            auto build_end = std::chrono::high_resolution_clock::now();
            std::cout << "List build time: " << std::chrono::duration_cast<std::chrono::microseconds>(build_end - build_start).count() << " ms" << std::endl;

            run_red_black_experiment(time_writer, number_list, m);
            run_chaining_experiment(time_writer, linked_list_writer, number_list, i, m);
            run_perfect_hashing_experiment(time_writer, rehashes_writer, number_list, i, m);
        }
        std::cout << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Experiment runtime: " << std::chrono::duration_cast<std::chrono::minutes>(end - start).count() << " m" << std::endl;
}

void ProjectOne::run_chaining_experiment(const CSVWriter &writer, const CSVWriter &list_writer, const std::vector<uint64_t> &list,
    const uint8_t &w, const uint32_t &m)
{
    // build time
    auto start = std::chrono::high_resolution_clock::now();
    HashingWithChaining hashing_with_chaining = HashingWithChaining(m, w, list);
    auto end = std::chrono::high_resolution_clock::now();
    auto build_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        hashing_with_chaining.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // results
    std::string time_result = "HashingWithChaining" "," + std::to_string(m) + "," + std::to_string(build_time) + "," + std::to_string(query_time) + "\n";
    std::string list_result = std::to_string(m) + "," + std::to_string(hashing_with_chaining.largest_linked_list()) + "\n";
    writer.append_result(time_result);
    list_writer.append_result(list_result);
}

void ProjectOne::run_red_black_experiment(const CSVWriter &writer, const std::vector<uint64_t> &list,  const uint32_t &m)
{
    // build time
    auto start = std::chrono::high_resolution_clock::now();
    RedBlackSearchTree red_black_search_tree = RedBlackSearchTree(list);
    auto end = std::chrono::high_resolution_clock::now();
    auto build_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        red_black_search_tree.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // results
    std::string time_result = "RedBlackSearchTree" "," + std::to_string(m) + "," + std::to_string(build_time) + "," + std::to_string(query_time) + "\n";
    writer.append_result(time_result);
}

void ProjectOne::run_perfect_hashing_experiment(const CSVWriter &writer, const CSVWriter &rehashes_writer, std::vector<uint64_t> &list, const uint8_t &w, const uint32_t &m)
{
    // build time
    auto start = std::chrono::high_resolution_clock::now();
    PerfectHashing perfect_hashing = PerfectHashing(list, w);
    auto end = std::chrono::high_resolution_clock::now();
    auto build_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        perfect_hashing.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto query_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // results
    std::string time_result = "PerfectHashing" "," + std::to_string(m) + "," + std::to_string(build_time) + "," + std::to_string(query_time) + "\n";
    std::string rehash_result = std::to_string(m) + "," + std::to_string(perfect_hashing.get_rehashes()) + "," + std::to_string(perfect_hashing.get_secondary_rehashes()) + "\n";
    writer.append_result(time_result);
    rehashes_writer.append_result(rehash_result);
}