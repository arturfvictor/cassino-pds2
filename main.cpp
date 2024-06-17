#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./dao/hpp/GenericDao.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, double player);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();

    Player* p1 = new Player(1, "Player1", 500.0);

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa", 150);

    vector<Game*> games;
    games.push_back(coinFlip);

    while (true) {
        showGameMenu(graphicModule, games, p1->getBalance());
        int gameId = inputModule->readIntInRange("", 0, games.size() - 1);
        games[gameId]->play(p1);
    }
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, double balance) {
    graphicModule->print("Saldo Atual: ", 80, false, false);
    graphicModule->println("R$ " + std::to_string(balance), 80, true, false);
    graphicModule->println("Escolha um dos jogos:", 80, false, true);

    int pos = 0;
    for (auto game : games) {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 80, false, false);
        pos++;
    }
}