cmake_minimum_required(VERSION 3.30)
project(Randomised_Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Randomised_Algorithms main.cpp)
add_library(Utils utils/NumberUtils.cpp
        utils/CSVWriter.cpp
        utils/CSVWriter.h)
add_library(Hashing hashing/MultiplyShiftHash.cpp
        hashing/MultiplyShiftHash.h
        hashing/HashingWithChaining.cpp
        hashing/HashingWithChaining.h
        hashing/RedBlackSearchTree.cpp
        hashing/RedBlackSearchTree.h
        hashing/PerfectHashing.cpp
        hashing/PerfectHashing.h
        hashing/SecondaryArray.cpp
        hashing/SecondaryArray.h
        hashing/MultiplyModPrimeHash.cpp
        hashing/MultiplyModPrimeHash.h)

target_link_libraries(Randomised_Algorithms Utils Hashing)