#ifndef BINGO
#define BINGO

#include <string>
#include <vector>

#include "./Game.hpp"
#include "../../module/input-module/hpp/InputModule.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class BingoGame : public Game {
    public:
        BingoGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name);
        void play(Player* player) override;
    private:
        bool DoOffer(int offer); 
        bool verificarCartelaCompleta(const std::vector<std::string>& cartela);
        int makedraw(std::vector<int>& numbers);
        bool marcarNumeroNaCartela(std::vector<std::string>& cartela, int numero);
        bool ValidateConfirmation(char *input);
        void ValidatePlayerCard(int ramdomnumber, std::vector<std :: string>& cartela);
        void GenerateCard(std::vector<std::string>& cartela);
        void printCard(const std::vector<std::string>& cartela);
        void showGameHeader(string name, float balance);
        bool validateInput(int option);
};

#endif