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
    this->graphicModule->print("BEM VINDO AO BINGO", 25, false, false);
    this->graphicModule->print("Saldo Atual: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 25, true, false);
    this->graphicModule->println("Aposta Mínima: R$ 70", 25, false, false);
}

int BingoGame::makedraw(std::vector<int>& numbers){
    int number;
    static int cont = 0;
    number = this->randomNumberGenerator->generate(1,75);
    for (const int& num : numbers) {
        if (num == number) {
            makedraw(numbers);
            cont++;
        }
    }if(cont == 200){
        return 0;
    }

    cont = 0;
    return number;
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
        this->graphicModule->print("O numero" + std::to_string(ramdomnumber) + "está na sua cartela? ", 25, false, false);
        scanf("%c", &char_input);
         bool validation;
         while(validation == true){
            validation = ValidateConfirmation(&char_input);
            this->graphicModule->clear();
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

bool BingoGame :: verificarCartelaCompleta(const std::vector<std::string>& cartela) {
    for (const auto& num : cartela) {
        if (num != "XX") {
            return false;
        }
    }
    return true;
}

bool BingoGame:: DoOffer(int offer){

        if(offer < 70){
            this->graphicModule->println("Aposta insuficiente", 25, true, false);
            return false;
        }else{
            return true;
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
    std::vector<int> old_numbers(75);
    bool player_offer;
    bool player_lose = false;
    int offer;

    showGameHeader(player->getName(), player -> getBalance());

    while(player_offer == false){
        this->graphicModule->clear();
        this->graphicModule->println("Faça sua aposta:", 25, true, false);
        scanf("%d", &offer);
       player_offer = DoOffer(offer);
    }

    GenerateCard(playercard);
    this->graphicModule->println("Aqui está sua cartela", 25, true, false);
    printCard(playercard);


    while(verificarCartelaCompleta(playercard) == false || player_lose == false){
        int ramdomnumber = makedraw(old_numbers);

        if(ramdomnumber = 0){
                this->graphicModule->println("Bingo Finalizado", 25, true, false);
                player_lose = true;
        }

        old_numbers.push_back(ramdomnumber);

        this->graphicModule->println("Numero sorteado: " + std::to_string(ramdomnumber), 25, true, false);

        ValidatePlayerCard(ramdomnumber, playercard);

        this->graphicModule->clear();
    }
    if(player_lose){
            this->graphicModule->println("YOU LOSE!!!", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance - offer);
            return;
    }
    if(verificarCartelaCompleta(playercard)){
            this->graphicModule->println("YOU WIN!!!", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance + offer);
            return;  
    }
}   