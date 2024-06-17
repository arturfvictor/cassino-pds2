#ifndef GAME
#define GAME

#include <string>
#include "../../model/hpp/Player.hpp"
#include "../../module/input-module/hpp/InputModule.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class Game {
    private:
        string name;
        double minimumBet;
    protected:
        GraphicModule* graphicModule;
        RandomNumberGenerator* randomNumberGenerator;
        InputModule* inputModule;
    public:
        Game(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name, double minimumBet);

        virtual void play(Player* player) = 0;

        void showGameHeader(string name, double balance);

        void setName(string name);
        string getName();

        void setMinimumBet(double minumumBet);
        double getMinimumBet();
};

#endif