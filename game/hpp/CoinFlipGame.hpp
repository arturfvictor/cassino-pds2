#ifndef COINFLIP
#define COINFLIP

#include <string>

#include "./Game.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class CoinFlipGame : public Game {
    public:
        CoinFlipGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, string name);
        void play(Player* player) override;
};

#endif