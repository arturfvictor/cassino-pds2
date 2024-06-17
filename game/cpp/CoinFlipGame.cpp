#include <cmath>

#include "../hpp/CoinFlipGame.hpp"

CoinFlipGame::CoinFlipGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name, double minimumBet):
 Game(graphicModule, randomNumberGenerator, inputModule, name, minimumBet) {}

void CoinFlipGame::play(Player* player) {
    bool firstExec = true;
    bool inputValidation;
    
    showGameHeader(player->getName(), player->getBalance());

    double bet = readBet(getMinimumBet(), player->getBalance());

    graphicModule->println("Cara ou Coroa?", 80, false, true);
    graphicModule->print("0 - ", 80, false, false);
    graphicModule->println("Cara", 80, true, false);
    graphicModule->print("1 - ", 80, false, false);
    graphicModule->println("Coroa", 80, true, false);

    int option = inputModule->readIntInRange("", 0, 1);

    graphicModule->clear();

    int result = randomNumberGenerator->generate(0, 2);   

    printOption(option);

    graphicModule->println("Sorteando........", 35, false, false);

    graphicModule->wait(750);
    graphicModule->clear();

    printOption(option);

    graphicModule->print("RESULTADO: " , 80, false, false); 
    if (result == 0) {
        graphicModule->println("Cara", 80, true, false);
    } else {
        graphicModule->println("Coroa", 80, true, false);
    }

    if (result == option) {
        double balance = player->getBalance();
        player->setBalance(balance + bet);

        graphicModule->println("VOCE GANHOU " + std::to_string(bet) + "!", 80, true, false);
        graphicModule->println("Novo saldo: R$", 80, false, false);
        graphicModule->println(std::to_string(player->getBalance()), 80, true, false);
    } else {
        double balance = player->getBalance();
        player->setBalance(balance - bet);

        graphicModule->print("EU...EU...EU...Você se...", 25, false, false);
        graphicModule->println("Perdeu!", 25, true, false);
        graphicModule->print("Novo saldo: R$", 80, false, false);
        graphicModule->println(std::to_string(player->getBalance()), 80, true, false);
    }

    graphicModule->wait(1250);
    graphicModule->clear();
}

double CoinFlipGame::readBet(double minimumBet, double balance) {
    graphicModule->println("Caso você ganhe o retorno será de 2X o valor apostado!", 80, true, true);
    graphicModule->print("Insira o valor da aposta: ", 80, false, false);
    
    double bet = inputModule->readDoubleInRange("", minimumBet, balance);

    graphicModule->println("--------------------------------", 1000, true, false);
    graphicModule->wait(750);

    return bet;
}

void CoinFlipGame::printOption(int option) {
    graphicModule->print("SELECIONADO: " , 1000, false, false); 
    
    if (option == 0) {
        graphicModule->println("Cara", 1000, true, false);
    } else {
        graphicModule->println("Coroa", 1000, true, false);
    }
}