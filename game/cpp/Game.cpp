#include "../hpp/Game.hpp"

Game::Game(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name):
 graphicModule(graphicModule), randomNumberGenerator(randomNumberGenerator), inputModule(inputModule), name(name) {};

void Game::setName(string name) {
    this->name = name;
}

string Game::getName() {
    return this->name;
}
