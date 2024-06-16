#include <cmath>

#include "../hpp/CoinFlipGame.hpp"

CoinFlipGame::CoinFlipGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name):
 Game(graphicModule, randomNumberGenerator, inputModule, name) {}

void CoinFlipGame::play(Player* player) {
    bool firstExec = true;
    bool inputValidation;
    
    showGameHeader(player->getName(), player->getBalance());

    while (firstExec == true || inputValidation == false) {
        firstExec = false;


        int option;
        scanf("%d", &option);

        inputValidation = validateInput(option);
    }
}

void CoinFlipGame::showGameHeader(string name, float balance) {
    this->graphicModule->clear();
    this->graphicModule->print("Olá, ", 25, false, false);
    this->graphicModule->println(name, 25, true, false);
    this->graphicModule->print("Saldo Atual: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 25, true, false);
    this->graphicModule->println("Aposta Mínima: R$ ", 25, false, false);
}

bool CoinFlipGame::validateInput(int option) {
    if (option < 0 || option > 1) {
        this->graphicModule->clear();
        this->graphicModule->print("Opção inválida, tente novamente!", 25, true, false);
        return false;
    }
    return true;
}