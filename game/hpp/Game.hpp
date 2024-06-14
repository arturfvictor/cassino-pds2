#ifndef GAME
#define GAME

#include <string>
#include "../../model/hpp/Player.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class Game {
    private:
        string name;
    protected:
        GraphicModule* graphicModule;
        RandomNumberGenerator* randomNumberGenerator;
    public:
        Game(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, string name);

        virtual void play(Player* player) = 0;

        void setName(string name);
        string getName();
};

#endif