#include "ProjectOne.h"
#include <chrono>

#include "../hashing/HashingWithChaining.h"
#include "../hashing/RedBlackSearchTree.h"
#include "../hashing/PerfectHashing.h"

void ProjectOne::runExperiments() {
    CSVWriter timeWriter("../analysis/results.csv", "algorithm,n,build,query");
    CSVWriter linkedListWriter("../analysis/linked_list.csv", "n,count");
    CSVWriter rehashesWriter("../analysis/rehashes.csv", "n,hashes,secondary_rehashes");

    std::cout << "Starting experiment one!" << std::endl;
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    for (uint8_t i = 10; i <= 25; ++i)
    {
        std::cout << "Running for 2^" << static_cast<int>(i) << ":" << std::endl;
        const uint32_t m = 1ULL<<i;
        for (uint8_t j = 0; j < 5; ++j)
        {
            std::cout << "Executing iteration " << static_cast<int>(j) + 1 << std::endl;
            std::chrono::time_point<std::chrono::steady_clock> buildStart = std::chrono::high_resolution_clock::now();
            std::vector<uint32_t> number_list = NumberUtils::generate_shuffled_list(m);
            std::chrono::time_point<std::chrono::steady_clock> buildEnd = std::chrono::high_resolution_clock::now();
            std::cout << "List build time: " << std::chrono::duration_cast<std::chrono::milliseconds>(buildEnd - buildStart).count() << " ms" << std::endl;

            runRedBlackExperiment(timeWriter, number_list, m);
            runChainingExperiment(timeWriter, linkedListWriter, number_list, i, m);
            runPerfectHashingExperiment(timeWriter, rehashesWriter, number_list, i, m);
        }
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    std::cout << "Experiment runtime: " << std::chrono::duration_cast<std::chrono::minutes>(end - start).count() << " m" << std::endl;
}

void ProjectOne::runChainingExperiment(const CSVWriter &writer, const CSVWriter &listWriter, const std::vector<uint32_t> &list,
    const uint8_t &w, const uint32_t &m)
{
    // build time
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    HashingWithChaining hashing_with_chaining = HashingWithChaining(m, w, list);
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        hashing_with_chaining.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // results
    std::string timeResult = "HashingWithChaining" "," + std::to_string(m) + "," + std::to_string(buildTime) + "," + std::to_string(queryTime) + "\n";
    std::string listResult = std::to_string(m) + "," + std::to_string(hashing_with_chaining.largest_linked_list()) + "\n";
    writer.appendResult(timeResult);
    listWriter.appendResult(listResult);
}

void ProjectOne::runRedBlackExperiment(const CSVWriter &writer, const std::vector<uint32_t> &list,  const uint32_t &m)
{
    // build time
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    RedBlackSearchTree red_black_search_tree = RedBlackSearchTree(list);
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        red_black_search_tree.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // results
    std::string timeResult = "RedBlackSearchTree" "," + std::to_string(m) + "," + std::to_string(buildTime) + "," + std::to_string(queryTime) + "\n";
    writer.appendResult(timeResult);
}

void ProjectOne::runPerfectHashingExperiment(const CSVWriter &writer, const CSVWriter &rehashesWriter, std::vector<uint32_t> &list, const uint8_t &w, const uint32_t &m)
{
    // build time
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    PerfectHashing perfect_hashing = PerfectHashing(list, w);
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    auto buildTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // query time
    start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        perfect_hashing.query(list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    auto queryTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // results
    std::string timeResult = "PerfectHashing" "," + std::to_string(m) + "," + std::to_string(buildTime) + "," + std::to_string(queryTime) + "\n";
    std::string rehashResult = std::to_string(m) + "," + std::to_string(perfect_hashing.get_rehashes()) + "," + std::to_string(perfect_hashing.get_secondary_rehashes()) + "\n";
    writer.appendResult(timeResult);
    rehashesWriter.appendResult(rehashResult);
}