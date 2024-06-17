#include "../hpp/Game.hpp"

Game::Game(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name, double minimumBet):
 graphicModule(graphicModule), randomNumberGenerator(randomNumberGenerator), inputModule(inputModule), name(name), minimumBet(minimumBet) {};

void Game::showGameHeader(string name, double balance) {
    this->graphicModule->clear();
    this->graphicModule->print("Olá, ", 50, false, false);
    this->graphicModule->println(name, 50, true, false);
    this->graphicModule->print("Bem vindo ao ", 50, false, false);
    this->graphicModule->println(this->getName() + "!", 50, true, false);
    this->graphicModule->print("Saldo Atual: ", 50, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 50, true, false);
    this->graphicModule->print("Aposta Mínima: R$ ", 50, false, false);
    this->graphicModule->println("R$ " + std::to_string(minimumBet), 50, true, false);
    this->graphicModule->println("--------------------------------", 1000, true, false);
    this->graphicModule->wait(250);
}

void Game::setName(string name) {
    this->name = name;
}

string Game::getName() {
    return this->name;
}

void Game::setMinimumBet(double minimumBet) {
    this->minimumBet = minimumBet;
}

double Game::getMinimumBet() {
    return this->minimumBet;
}
