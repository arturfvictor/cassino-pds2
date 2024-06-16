#ifndef COINFLIP
#define COINFLIP

#include <string>

#include "./Game.hpp"
#include "../../module/input-module/hpp/InputModule.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class CoinFlipGame : public Game {
    public:
        CoinFlipGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name);
        void play(Player* player) override;
    private:
        void showGameHeader(string name, float balance);
        bool validateInput(int option);
};

#endif