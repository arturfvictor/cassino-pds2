#include "../hpp/CoinFlipGame.hpp"

CoinFlipGame::CoinFlipGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, string name):
 Game(graphicModule, randomNumberGenerator, name) {}

void CoinFlipGame::play(Player* player) {
    this->graphicModule->print("Cara ou coroa?", 14, false, true);
}