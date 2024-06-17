#ifndef JOGODOBICHO_HPP
#define JOGODOBICHO_HPP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "./Game.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;
using std::vector;
using std::pair; // Adicionado

class JogoDoBicho : public Game {
private:
    vector<pair<string, int>> animais;
    vector<pair<string, int>> modosdeaposta;

public:
    JogoDoBicho(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator,InputModule* inputModule, string name);
    void play(Player* player) override;
    int escolherAnimal(const string& animalEscolhido);
    void showGameHeader(string name, float balance);
    void ApostarDezena();
    void ApostarCentena();
    void ApostarAnimal();
    void mostrarAnimal();
};

#endif
