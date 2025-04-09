#ifndef PROJECTTWO_H
#define PROJECTTWO_H
#include <cstdint>


class Sketch;
class CSVWriter;
class KeyValueHashingWithChaining;
class ProjectTwo {
public:
    static void run_experiments();
private:
    static void run_exercise_5();
    static void run_exercise_7();
    static void key_value_experiment(const CSVWriter &writer, KeyValueHashingWithChaining &hashing_with_chaining, const uint64_t &n);
    static void sketch_experiment(const CSVWriter &writer, Sketch &sketch, const uint64_t &n);
    static void run_exercise_8();
    static void run_exercise_9();
    static void run_exercise_12();
};

#endif //PROJECTTWO_H
