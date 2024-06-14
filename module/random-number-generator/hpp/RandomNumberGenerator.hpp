#ifndef RANDOMNUMBERGENERATOR
#define RANDOMNUMBERGENERATOR

class RandomNumberGenerator {
    public:
        virtual int generate() = 0;
        virtual int generate(int start, int end) = 0;
};

# endif