#include <iostream>
#include "experiments/ProjectTwo.h"
#include "hashing/hash_functions/BinarySearchHash.h"
#include "hashing/hash_functions/ModPrimeFor128BitHash.h"

using namespace std;

int main()
{
    ProjectTwo::run_experiments();

    return 0;
}