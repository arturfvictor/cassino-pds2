#ifndef BASICRANDOMNUMBERGENERATOR
#define BASICRANDOMNUMBERGENERATOR

#include "./RandomNumberGenerator.hpp"

class BasicRandomNumberGenerator : public RandomNumberGenerator {
    private:
        unsigned int seed;
    public:
        /// @brief Construtor do BasicRandomNumberGenerator
        BasicRandomNumberGenerator();
        int generate();
        int generate(int start, int end);
};

# endif