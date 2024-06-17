#ifndef DADOS
#define DADOS

#include <string>

#include "./Game.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class Dados : public Game
{
public:
    Dados(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator,
          InputModule *inputModule, string name, double minimumBet);
    void play(Player *player) override;

private:
    void escolha_2numeros(Player *player);
    void escolha_maior_menor(Player *player);
    void imprime_dados(int n);
};

#endif