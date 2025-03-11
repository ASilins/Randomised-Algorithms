#include <iostream>
#include <vector>
#include "hashing/HashingWithChaining.h"
#include "hashing/PerfectHashing.h"
#include "hashing/RedBlackSearchTree.h"
#include "utils/CSVWriter.h"
#include "utils/NumberUtils.h"
using namespace std;

void runChainingExperiment(const CSVWriter &writer, const vector<uint32_t> &list, const uint8_t &w, const uint32_t &m) {
    // build time
    chrono::time_point<chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    HashingWithChaining hashing_with_chaining = HashingWithChaining(m, w, list);
    chrono::time_point<chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        hashing_with_chaining.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // results
    writer.appendResult("HashingWithChaining", m, buildTime, queryTime);
}

void runRedBlackExperiment(const CSVWriter &writer, const vector<uint32_t> &list,  const uint32_t &m) {
    // build time
    chrono::time_point<chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    RedBlackSearchTree red_black_search_tree = RedBlackSearchTree(list);
    chrono::time_point<chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        red_black_search_tree.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // results
    writer.appendResult("RedBlackSearchTree", m, buildTime, queryTime);
}

void runPerfectHashingExperiment(const CSVWriter &writer, std::vector<uint32_t> &list, const uint8_t &w, const uint32_t &m) {
    // build time
    chrono::time_point<chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    PerfectHashing perfect_hashing = PerfectHashing(list, w);
    chrono::time_point<chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        perfect_hashing.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // results
    writer.appendResult("PerfectHashing", m, buildTime, queryTime);
}

int main()
{
    CSVWriter csvWriter("../analysis/results.csv");

    for (uint8_t i = 5; i < 21; ++i)
    {
        const uint32_t m = 1ULL<<i;
        for (int j = 0; j < 10; ++j)
        {
            vector<uint32_t> number_list = NumberUtils::generate_shuffled_list(m);
            runRedBlackExperiment(csvWriter, number_list, m);
            runChainingExperiment(csvWriter, number_list, i, m);
            runPerfectHashingExperiment(csvWriter, number_list, i, m);
        }
    }
    return 0;
}