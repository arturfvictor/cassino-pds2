#include "../hpp/Game.hpp"

Game::Game(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, string name):
 graphicModule(graphicModule), randomNumberGenerator(randomNumberGenerator), name(name) {};

void Game::setName(string name) {
    this->name = name;
}

string Game::getName() {
    return this->name;
}
