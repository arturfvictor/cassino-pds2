#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./dao/hpp/GenericDao.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();

    Player* p1 = new Player(1, "Player1", 16000.0);

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, "Cara ou Coroa");

    vector<Game*> games;
    games.push_back(coinFlip);

    showGameMenu(graphicModule, games);
    int gameId;
    scanf("%d", &gameId);

    games[gameId]->play(p1);
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games) {
    graphicModule->print("Escolha um dos jogos:\n", 25, false, true);
    int pos = 0;
    for (auto game : games) {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 25, false, false);
        pos++;
    }
}