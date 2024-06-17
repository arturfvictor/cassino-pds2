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
    for (int num : numbers) {
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

bool BingoGame::ValidateConfirmation(string input){
    if (input == "S" || input == "s" || input == "sim" ||input == "N" || input == "n" || input == "nao") {
        return true;
    }
        this->graphicModule->clear();
        this->graphicModule->print("Opção inválida, tente novamente!", 25, true, false);
        return false;

}

void BingoGame::GenerateCard(std::vector<int>& cartela) {
    for (int i = 0; i < 25; ++i) {
        int num;
        num = randomNumberGenerator ->generate(1,75);
       cartela[i] = num;
    }
}

void BingoGame:: printCard(const std::vector<int>& cartela) {
    for (int i = 0; i < cartela.size(); ++i) {
        std::cout << std::setw(3) << cartela[i] << " ";
        if ((i + 1) % 5 == 0)
            std::cout << std::endl;
    }
}

void BingoGame::ValidatePlayerCard(int ramdomnumber, std::vector<int>& cartela){
        this->graphicModule->clear();
        string char_input;
        this->graphicModule->print("O numero " + std::to_string(ramdomnumber) + " está na sua cartela? ", 25, false, false);
        char_input = inputModule->readString("");
         bool validation = false;
         while(validation == false){
            validation = ValidateConfirmation(char_input);
            this->graphicModule->clear();
         }
        if(validation == true){
            if(char_input == "sim" || char_input == "S" || char_input == "s"){
                this->graphicModule->println("digite o numero: ", 25, false, false);
                int card_number;
                card_number = inputModule->readInt("");
                if (marcarNumeroNaCartela(cartela,card_number) == true)
                {
                    this->graphicModule->print("Número " + std::to_string(card_number)+ " marcado na cartela.", 25, false, false);
                    printCard(cartela);
                 } else {
                this->graphicModule->println("Número não está na sua cartela.", 25, false, false);
                printCard(cartela);
               }
                
            }

        }else {
            return;
        }

}

/*bool BingoGame :: verificarCartelaCompleta(const std::vector<int>& cartela) {
    for (int num : cartela) {
        if (num != "-1") {
            return false;
        }
    }
    return true;
}*/

bool BingoGame:: DoOffer(int offer){

        if(offer < 70){
            this->graphicModule->println("Aposta insuficiente", 25, true, false);
            return false;
        }else{
            return true;
        }
}

bool BingoGame:: marcarNumeroNaCartela(std::vector<int>& cartela, int numero) {
    bool marcado = false;
    for (int i = 0; i < cartela.size(); ++i) {
        if (cartela[i] == numero) {
            cartela[i] = 0; // Marcar o número com -1 (ou outro valor que indique marcação)
            marcado = true;
            break; // Encerra o loop assim que o número for marcado
        }
    }
    return marcado;
}

void BingoGame::play(Player* player){
    
    
    std::vector<int> playercard(25);
    std::vector<int> old_numbers(75);

    bool player_offer = false;
    bool player_lose = false;
    int offer;
    int ramdomnumber = 0;

    showGameHeader(player->getName(), player -> getBalance());

    while(player_offer == false){
        this->graphicModule->clear();
        this->graphicModule->println("Faça sua aposta:", 25, true, false);
        offer = inputModule->readInt("");
        player_offer = DoOffer(offer);
    }

    GenerateCard(playercard);
    this->graphicModule->println("Aqui está sua cartela", 25, true, false);
    printCard(playercard);
    while(/*verificarCartelaCompleta(playercard) == false || player_lose == false*/ 1){
        ramdomnumber = makedraw(old_numbers);
        if(ramdomnumber = 0){
                this->graphicModule->println("Bingo Finalizado", 25, true, false);
                player_lose = true;
        }

        this->graphicModule->print("Numero sorteado: " + std::to_string(ramdomnumber), 25, true, false);

        ValidatePlayerCard(ramdomnumber, playercard);

        old_numbers.push_back(ramdomnumber);

        this->graphicModule->clear();
    }
    if(player_lose){
            this->graphicModule->println("YOU LOSE!!!", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance - offer);
            return;
    }
    /*if(verificarCartelaCompleta(playercard)){
            this->graphicModule->println("YOU WIN!!!", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance + offer);
            return;  
    }*/
}   