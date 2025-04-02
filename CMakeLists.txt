cmake_minimum_required(VERSION 3.30)
project(Randomised_Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Randomised_Algorithms main.cpp)
add_library(Utils utils/NumberUtils.cpp
        utils/CSVWriter.cpp
        utils/CSVWriter.h)
add_library(Hashing hashing/hash_functions/MultiplyShiftHash.cpp
        hashing/hash_functions/MultiplyShiftHash.h
        hashing/hashing_with_chaining/HashingWithChaining.cpp
        hashing/hashing_with_chaining/HashingWithChaining.h
        hashing/red_black_tree/RedBlackSearchTree.cpp
        hashing/red_black_tree/RedBlackSearchTree.h
        hashing/perfect_hashing/PerfectHashing.cpp
        hashing/perfect_hashing/PerfectHashing.h
        hashing/perfect_hashing/SecondaryArray.cpp
        hashing/perfect_hashing/SecondaryArray.h
        hashing/hash_functions/MultiplyModPrimeHash.cpp
        hashing/hash_functions/MultiplyModPrimeHash.h
        hashing/hash_functions/FourWiseIndependentHash.cpp
        hashing/hash_functions/FourWiseIndependentHash.h
        hashing/hashing_with_chaining/KeyValueHashingWithChaining.cpp
        hashing/hashing_with_chaining/KeyValueHashingWithChaining.h)
add_library(Experiments experiments/ProjectOne.cpp experiments/ProjectOne.h)

target_link_libraries(Randomised_Algorithms Utils Hashing Experiments)
