#include "ProjectTwo.h"

#include <iostream>

#include "../hashing/hash_functions/FourWiseIndependentHash.h"
#include "../hashing/hash_functions/MultiplyShiftHash.h"
#include "../hashing/hashing_with_chaining/KeyValueHashingWithChaining.h"
#include "../utils/CSVWriter.h"

void ProjectTwo::run_experiments() {
    run_exercise_5();
    run_exercise_7();
    run_exercise_8();
    run_exercise_9();
    run_exercise_12();
}

void ProjectTwo::run_exercise_5() {
    std::cout << "Running exercise 5: " << std::endl;
    CSVWriter multiply_shift_writer("../analysis/ProjectTwo/ex5_multiply_shift.csv", "n,time");
    CSVWriter four_wise_writer("../analysis/ProjectTwo/ex5_four_wise.csv", "n,time");

    // Setup hash function. We still use the fact that we shift the bits, but we use numbers in range [0, 10^6-1]
    constexpr uint8_t w = 20;
    auto multiply_shift_hash = MultiplyShiftHash(w);
    auto four_wise_hash = FourWiseIndependentHash(w);
    auto list_of_numbers = NumberUtils::generate_list(0, 1e6 - 1);

    for (uint64_t i = 0; i < 1e6; ++i) {
        auto start = std::chrono::high_resolution_clock::now();

        for (const auto number: list_of_numbers) {
            (void)multiply_shift_hash.hash(number);
        }

        auto end = std::chrono::high_resolution_clock::now();
        const auto multiply_shift_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        for (const auto number: list_of_numbers) {
            (void)four_wise_hash.hash(number);
        }
        end = std::chrono::high_resolution_clock::now();
        const auto four_wise_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::string multiply_shift_result = std::to_string(i) + "," + std::to_string(multiply_shift_time) + "\n";
        std::string four_wise_result = std::to_string(i) + "," + std::to_string(four_wise_time) + "\n";
        multiply_shift_writer.append_result(multiply_shift_result);
        four_wise_writer.append_result(four_wise_result);
    }
}

void ProjectTwo::run_exercise_7() {
    std::cout << "Running exercise 5: " << std::endl;
    // TODO:
    //  Make 10^9 updates. One experiment for each n in the form of n = 2^N with N = 6, 7, ..., 28.
    //  The i'th update should be ((i mod n), 1). The sketch should have array of 2^7, 2^10, 2^20.

    CSVWriter hashing_with_chaining_writer("../analysis/ProjectTwo/ex7_hashing_with_chaining.csv", "n,time");
    CSVWriter sketch_7_writer("../analysis/ProjectTwo/ex7_sketch_7.csv", "n,time");
    CSVWriter sketch_10_writer("../analysis/ProjectTwo/ex7_sketch_10.csv", "n,time");
    CSVWriter sketch_20_writer("../analysis/ProjectTwo/ex7_sketch_20.csv", "n,time");

    for (int N = 6; N <= 28; ++N) {
        // 2^N
        const uint64_t n = 1ULL << N;
        // TODO: Init Sketch with 2^7
        // TODO: Init Sketch with 2^10
        // TODO: Init Sketch with 2^20
        auto multiply_shift_table = KeyValueHashingWithChaining(n, N);

        key_value_experiment(hashing_with_chaining_writer, multiply_shift_table, n);
        // TODO: Run sketch experiments
    }
}

void ProjectTwo::key_value_experiment(const CSVWriter &writer, KeyValueHashingWithChaining &hashing_with_chaining, const uint64_t &n) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 1; i <= 1e9; ++i) {
        const uint64_t i_th_update = i % n;
        hashing_with_chaining.update(std::make_tuple(i_th_update, 1));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::string result_string = std::to_string(n) + "," + std::to_string(result) + "\n";
    writer.append_result(result_string);
}

void sketch_experiment(const CSVWriter &writer, const uint64_t &n) {
    auto start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 1; i <= 1e9; ++i) {
        const uint64_t i_th_update = i % n;
        // TODO: Update sketch
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::string result_string = std::to_string(n) + "," + std::to_string(result) + "\n";
    writer.append_result(result_string);
}

void ProjectTwo::run_exercise_8() {
    std::cout << "Running exercise 8: " << std::endl;
    // TODO:
    //  Make 10^3 updates. The i'th update is (i,i^2). Measure relative error and plot it as a function of r
    //  r = 2^3, 2^4, .., 2^10. Run 100 times for each r.
}

void ProjectTwo::run_exercise_9() {
    std::cout << "Running exercise 9: " << std::endl;
    // TODO:
    //  Repeat exercise 8 but with different hash functions. k = (a*x + b) >> 33
}

void ProjectTwo::run_exercise_12() {
    std::cout << "Running exercise 12: " << std::endl;
    // TODO:
    //  Evaluate mod operation 10^6 times.
}