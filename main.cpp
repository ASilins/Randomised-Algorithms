#include <iostream>
#include <random>
#include <vector>
#include "hashing/HashFunction.h"
#include "hashing/HashingWithChaining.h"
#include "hashing/PerfectHashing.h"
#include "hashing/RedBlackSearchTree.h"
#include "utils/NumberUtils.h"
using namespace std;

int main()
{
    constexpr uint8_t w = 20;
    // 2^w
    constexpr uint32_t m = 1<<w;

    // setup
    vector<uint32_t> number_list(m);
    number_list = NumberUtils::generate_shuffled_list(m);

    HashingWithChaining hashing_with_chaining = HashingWithChaining(m, w);
    RedBlackSearchTree red_black_search_tree = RedBlackSearchTree();

    cout << "Starting experiment!" << endl;
    cout << "Hashing with chaining:" << endl;
    chrono::time_point<chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        hashing_with_chaining.insert(number_list.at(i));
    }
    chrono::time_point<chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
    cout << "Insert time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        hashing_with_chaining.query(number_list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    cout << "Query time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    cout << "Red-Black search tree:" << endl;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        red_black_search_tree.insert(number_list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    cout << "Insert time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        red_black_search_tree.query(number_list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    cout << "Query time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    // hashing_with_chaining.print_table();

    cout << "Perfect hashing:" << endl;
    start = std::chrono::high_resolution_clock::now();
    PerfectHashing perfect_hashing = PerfectHashing(number_list, w);
    end = std::chrono::high_resolution_clock::now();
    cout << "Build time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m; i++) {
        perfect_hashing.query(number_list.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    cout << "Query time taken: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    return 0;
}