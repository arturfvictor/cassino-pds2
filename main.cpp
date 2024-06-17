#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./game/hpp/BingoGame.hpp"
#include "./dao/hpp/GenericDao.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();

    Player* p1 = new Player(1, "Player1", 16000.0);

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa");
    Game* bingo = new BingoGame(graphicModule, randomNumberGenerator, inputModule, "Bingo");

    vector<Game*> games;
    games.push_back(coinFlip);
    games.push_back(bingo);

    while (true) {
        showGameMenu(graphicModule, games);
        int gameId = inputModule->readIntInRange("", 0, games.size() - 1);
        games[gameId]->play(p1);
    }
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games) {
    graphicModule->print("Escolha um dos jogos:\n", 25, false, true);
    int pos = 0;
    for (auto game : games) {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 25, false, false);
        pos++;
    }
}