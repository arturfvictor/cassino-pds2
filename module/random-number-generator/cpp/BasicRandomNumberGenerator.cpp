#include <random>
#include <iostream>

#include "../hpp/BasicRandomNumberGenerator.hpp"

BasicRandomNumberGenerator::BasicRandomNumberGenerator() {
    this->seed = time(NULL);
    srand(seed);
}

int BasicRandomNumberGenerator::generate() {
    return rand();
}

int BasicRandomNumberGenerator::generate(int start, int end) {
    return start + (rand() % (end - start));
}