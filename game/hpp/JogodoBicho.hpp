#ifndef JOGODOBICHO_HPP
#define JOGODOBICHO_HPP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "./Game.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::pair; // Adicionado
using std::string;
using std::vector;

class JogoDoBicho : public Game
{
private:
    string tipoSorteio;
    std::vector<std::pair<std::string, int>> animais;
    std::vector<std::string> modosdeaposta;

public:
    JogoDoBicho(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name, double minimumBet);
    void play(Player *player) override;
    int escolherAnimal(const string &animalEscolhido);
    void mostrarAnimal();
    bool sorteio(const string &tipoSorteio, int numeroEscolhido);
    double readBet(double minimumBet, double balance);
};

#endif
