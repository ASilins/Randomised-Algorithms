cmake_minimum_required(VERSION 3.30)
project(Randomised_Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Randomised_Algorithms main.cpp)
add_library(Utils utils/NumberUtils.cpp)
add_library(Hashing hashing/HashFunction.cpp hashing/HashingWithChaining.cpp
        hashing/RedBlackSearchTree.cpp
        hashing/RedBlackSearchTree.h
        hashing/PerfectHashing.cpp
        hashing/PerfectHashing.h
        hashing/SecondaryArray.cpp
        hashing/SecondaryArray.h)

target_link_libraries(Randomised_Algorithms Utils Hashing)