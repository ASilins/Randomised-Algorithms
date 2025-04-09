#include "ProjectTwo.h"

#include <iostream>

#include "../hashing/hash_functions/FourWiseIndependentHash.h"
#include "../hashing/hash_functions/MultiplyShiftHash.h"
#include "../hashing/hashing_with_chaining/KeyValueHashingWithChaining.h"
#include "../sketch/Sketch.h"
#include "../utils/CSVWriter.h"
#include "../utils/TimerUtils.h"

void ProjectTwo::run_experiments() {
    // TimerUtils::time_experiment_with_print("Running experiment: 5", run_exercise_5);
    // TimerUtils::time_experiment_with_print("Running experiment: 7", run_exercise_7);
    // TimerUtils::time_experiment_with_print("Running experiment: 8", run_exercise_8);
    // TimerUtils::time_experiment_with_print("Running experiment: 9", run_exercise_9);
    // TimerUtils::time_experiment_with_print("Running experiment: 12", run_exercise_12);
}

void ProjectTwo::run_exercise_5() {
    CSVWriter multiply_shift_writer("../analysis/ProjectTwo/ex5_multiply_shift.csv", "n,time");
    CSVWriter four_wise_writer("../analysis/ProjectTwo/ex5_four_wise.csv", "n,time");

    // Setup hash function. We still use the fact that we shift the bits, but we use numbers in range [0, 10^6-1]
    constexpr uint8_t w = 20;
    auto multiply_shift_hash = MultiplyShiftHash(w);
    auto four_wise_hash = FourWiseIndependentHash(w);
    auto list_of_numbers = NumberUtils::generate_list(0, 1e6 - 1);

    for (uint64_t i = 0; i < 10; ++i) {
        const auto multiply_shift_time = TimerUtils::time_experiment([&list_of_numbers, &multiply_shift_hash]() {
            for (const auto number: list_of_numbers) {
                (void)multiply_shift_hash.hash(number);
            }
        });

        const auto four_wise_time = TimerUtils::time_experiment([&list_of_numbers, &four_wise_hash]() {
            for (const auto number: list_of_numbers) {
                (void)four_wise_hash.hash(number);
            }
        });

        multiply_shift_writer.append_row(std::to_string(i), std::to_string(multiply_shift_time));
        four_wise_writer.append_row(std::to_string(i), std::to_string(four_wise_time));
    }
}

void ProjectTwo::run_exercise_7() {
    // TODO:
    //  Make 10^9 updates. One experiment for each n in the form of n = 2^N with N = 6, 7, ..., 28.
    //  The i'th update should be ((i mod n), 1). The sketch should have array of 2^7, 2^10, 2^20.

    CSVWriter hashing_with_chaining_writer("../analysis/ProjectTwo/ex7_hashing_with_chaining.csv", "n,time");
    CSVWriter sketch_7_writer("../analysis/ProjectTwo/ex7_sketch_7.csv", "n,time");
    CSVWriter sketch_10_writer("../analysis/ProjectTwo/ex7_sketch_10.csv", "n,time");
    CSVWriter sketch_20_writer("../analysis/ProjectTwo/ex7_sketch_20.csv", "n,time");

    for (int N = 6; N <= 8; ++N) {
        // 2^N
        const uint64_t n = 1ULL << N;
        auto multiply_shift_table = KeyValueHashingWithChaining(n, N);
        auto sketch_7 = Sketch(7);
        auto sketch_10 = Sketch(10);
        auto sketch_20 = Sketch(20);

        key_value_experiment(hashing_with_chaining_writer, multiply_shift_table, n);
        sketch_experiment(sketch_7_writer, sketch_7, n);
        sketch_experiment(sketch_10_writer, sketch_10, n);
        sketch_experiment(sketch_20_writer, sketch_20, n);
    }
}

void ProjectTwo::key_value_experiment(const CSVWriter &writer, KeyValueHashingWithChaining &hashing_with_chaining, const uint64_t &n) {
    std::cout << "Running Hashing With Chaining experiment for n = " << n << std::endl;
    const auto result = TimerUtils::time_experiment([&hashing_with_chaining, &n]() {
        for (uint64_t i = 1; i <= 1e9; ++i) {
            const uint64_t i_th_update = i % n;
            hashing_with_chaining.update(std::make_tuple(i_th_update, 1));
        }
    });
    writer.append_row(std::to_string(n), std::to_string(result));
}

void ProjectTwo::sketch_experiment(const CSVWriter &writer, Sketch &sketch, const uint64_t &n) {
    std::cout << "Running Sketch experiment for n = " << n << std::endl;
    const auto result = TimerUtils::time_experiment([&sketch, &n]() {
        for (uint64_t i = 1; i <= 1e9; ++i) {
            const uint64_t i_th_update = i % n;
            sketch.update(i_th_update, 1);
        }
    });
    writer.append_row(std::to_string(n), std::to_string(result));
}

void ProjectTwo::run_exercise_8() {
    // TODO:
    //  Make 10^3 updates. The i'th update is (i,i^2). Measure relative error and plot it as a function of r
    //  r = 2^3, 2^4, .., 2^10. Run 100 times for each r.
}

void ProjectTwo::run_exercise_9() {
    // TODO:
    //  Repeat exercise 8 but with different hash functions. k = (a*x + b) >> 33
}

void ProjectTwo::run_exercise_12() {
    // TODO:
    //  Evaluate mod operation 10^6 times.
}