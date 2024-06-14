#include <iostream>
#include <string>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./dao/hpp/GenericDao.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();
    // PlayerDao* playerDao = new PlayerMapDao();

    Player* p1 = new Player(1, "Artur1", 22000.54);

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, "Cara ou Coroa");
    coinFlip->play(p1);
}