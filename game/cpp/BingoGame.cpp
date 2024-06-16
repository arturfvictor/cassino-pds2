#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>

#include "../hpp/BingoGame.hpp"

BingoGame::BingoGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name):
 Game(graphicModule, randomNumberGenerator, inputModule, name) {}


void BingoGame::showGameHeader(string name, float balance) {
    this->graphicModule->clear();
    this->graphicModule->print("Olá, ", 25, false, false);
    this->graphicModule->println(name, 25, true, false);
    this->graphicModule->print("Saldo Atual: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 25, true, false);
    this->graphicModule->println("Aposta Mínima: R$ ", 25, false, false);
}

int BingoGame::makedraw(){
    this->randomNumberGenerator->generate();
}

bool BingoGame::ValidateConfirmation(char *input){
    if (input == "S" || input == "s" || input == "sim" ||input == "N" || input == "n" || input == "nao") {
        return true;
    }
        this->graphicModule->clear();
        this->graphicModule->print("Opção inválida, tente novamente!", 25, true, false);
        return false;

}


void BingoGame::GenerateCard(std::vector<std::string>& cartela) {
    for (int i = 0; i < 24; ++i) {
        int num;
        do {
            num = rand() % 75 + 1; // Números de 1 a 75
        } while (std::find(cartela.begin(), cartela.end(), num) != cartela.end());
        cartela[i] = (num < 10 ? "0" : "") + std::to_string(num); // Garantir duas posições
    }
}

void BingoGame:: printCard(const std::vector<std::string>& cartela) {
    for (int i = 0; i < 24; ++i) {
        std::cout << std::setw(3) << cartela[i] << " ";
        if ((i + 1) % 5 == 0)
            std::cout << std::endl;
    }
}

void BingoGame::ValidatePlayerCard(int ramdomnumber, std::vector<std ::string>& cartela){
        this->graphicModule->clear();
        char char_input;
        this->graphicModule->print("O numero sorteado está na sua cartela? ", 25, false, false);
        scanf("%c", &char_input);
         bool validation;
         while(validation == true){
            validation = ValidateConfirmation(&char_input);
         }
        if(validation == true){
            if(&char_input == "sim" || &char_input == "S" || &char_input == "s"){
                this->graphicModule->println("digite o numero: ", 25, false, false);
                int card_number;
                scanf("%d", &card_number);
                if (marcarNumeroNaCartela(cartela,card_number))
                {
                    std::cout << "Número " << card_number << " marcado na cartela." << std::endl;
                    printCard(cartela);
                 } else {
                std::cout << "Número não está na sua cartela." << std::endl;
                printCard(cartela);
               }
                
            }

        }else {
            return;
        }

}

bool BingoGame:: marcarNumeroNaCartela(std::vector<std::string>& cartela, int numero) {
    bool marcado = false;
    std::string numeroStr = (numero < 10 ? "0" : "") + std::to_string(numero);
    for (int i = 0; i < 24; ++i) {
        if (cartela[i] == numeroStr) {
            cartela[i] = "XX"; // Marcar o número com 'XX'
            marcado = true;
        }
    }
    return marcado;
}
void BingoGame::play(Player* player){
    
    std::vector<std::string> playercard(24);
    GenerateCard(playercard);
    printCard(playercard);
    int ramdomnumber = makedraw();
    this->graphicModule->println("Numero sorteado: " + std::to_string(ramdomnumber), 25, true, false);
    ValidatePlayerCard(ramdomnumber, playercard);
    this->graphicModule->clear();
}