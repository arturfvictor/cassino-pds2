#ifndef BINGO
#define BINGO

#include <string>
#include <vector>

#include "./Game.hpp"
#include "../../module/input-module/hpp/InputModule.hpp"
#include "../../module/graphic-module/hpp/GraphicModule.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

using std::string;

class BingoGame : public Game
{
public:
    BingoGame(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name, double minimum_bet);
    void play(Player *player) override;

private:
    bool DoOffer(int offer);
    bool verificarCartelaCompleta(const std::vector<int> &cartela);
    bool HasCommonNumber(const std::vector<int> &cartela, const std::vector<int> &old_numbers);
    int makedraw(std::vector<int> &numbers);
    bool MarkPlayerCard(std::vector<int> &card, int number);
    bool ValidateConfirmation(string input);
    void ValidatePlayerCard(int ramdomnumber, std::vector<int> &cartela);
    void GenerateCard(std::vector<int> &cartela);
    void printCard(const std::vector<int> &cartela);
    bool validateInput(int option);
};

#endif