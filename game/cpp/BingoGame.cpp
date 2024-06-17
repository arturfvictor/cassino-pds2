#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "../hpp/BingoGame.hpp"

using std::flush;
using namespace std::chrono;
using namespace std::this_thread;

BingoGame::BingoGame(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name):
 Game(graphicModule, randomNumberGenerator, inputModule, name) {}


void BingoGame::showGameHeader(string name, float balance) {
    this->graphicModule->clear();
    this->graphicModule->println("BEM VINDO AO BINGO", 25, false, false);
    this->graphicModule->print("Saldo Atual: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 25, true, false);
    this->graphicModule->println("Aposta Mínima: R$ 70", 25, false, false);
}

int BingoGame::makedraw(std::vector<int>& numbers){
    int number;
    number = this->randomNumberGenerator->generate(1,26);
    for (int num : numbers) {
        if (num == number) {
             return 0;
        }
    }
    return number;
}

bool BingoGame::ValidateConfirmation(string input){
    if (input == "S" || input == "s" || input == "sim" ||input == "N" || input == "n" || input == "nao" || input == "não") {
        return true;
    }
        this->graphicModule->clear();
        this->graphicModule->print("Opção inválida, tente novamente!", 25, true, false);
        sleep_for(milliseconds(500));   
        return false;

}


void BingoGame::GenerateCard(std::vector<int>& cartela) {
    std::vector<int> uniqueNumbers;
    cartela.resize(25); // Certifica-se de que o vetor tenha o tamanho correto
    for (int i = 0; i < 25 ; ++i) {
        int num;
        do {
            num = randomNumberGenerator->generate(1, 26);
        } while (std::find(uniqueNumbers.begin(), uniqueNumbers.end(), num) != uniqueNumbers.end());
        
        uniqueNumbers.push_back(num);
        cartela[i] = num;
    }
}

void BingoGame:: printCard(const std::vector<int>& cartela) {
    this->graphicModule->println("", 25, false, false);
    for (int i = 0; i < cartela.size(); ++i) {
        if(cartela[i]== 0){
            this->graphicModule->print("X", 80, false, false);
        }else{
        this->graphicModule->print(std::to_string(cartela[i]), 80, false, true);
        }
        if ((i + 1) % 5 != 0) {
            this->graphicModule->print(" | ", 80, false, false);
        } else {
            this->graphicModule->println("", 25, false, false);
        }
    }
}

void BingoGame::ValidatePlayerCard(int ramdomnumber, std::vector<int>& cartela){

        string char_input;

         bool validation = false;
         while(validation == false){
            this->graphicModule->clear();
            this->graphicModule->print("O numero " + std::to_string(ramdomnumber) + " está na sua cartela? ", 70, false, false);
            this->graphicModule->println("",25,false,false);
            printCard(cartela);
            char_input = inputModule->readString("");
            validation = ValidateConfirmation(char_input);
            this->graphicModule->clear();
         }
        if(validation == true){
            if(char_input == "sim" || char_input == "S" || char_input == "s"){
                this->graphicModule->println("digite o numero: ", 80, false, false);
                int card_number;
                card_number = inputModule->readInt("");
                if(card_number = ramdomnumber){
                    if (marcarNumeroNaCartela(cartela,ramdomnumber) == true)
                    {
                        this->graphicModule->print("Número " + std::to_string(card_number)+ " marcado na cartela.", 80, false, false);
                        printCard(cartela);
                        sleep_for(milliseconds(1000));    
                    } else {
                this->graphicModule->println("Número não está na sua cartela.", 80, false, false);
                printCard(cartela);
                
                sleep_for(milliseconds(1000));     
               }
                
            }
            }
        }else {

            return;
        }

}

bool BingoGame :: verificarCartelaCompleta(const std::vector<int>& cartela) {
    for (int num : cartela) {
        if (num != 0) {
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

bool BingoGame::HasCommonNumber(const std::vector<int>& cartela, const std::vector<int>& old_numbers) {
    for (const int& num_cartela : cartela) {
        for (const int& num_old : old_numbers) {
            if ((num_cartela == num_old) && num_cartela != 0) {
                return true;
            }
        }
    }
    return false;
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
    
    
    std::vector<int> playercard(5);
    std::vector<int> old_numbers(76);

    bool player_offer = false;
    bool player_lose = false;
    int offer;
    

    showGameHeader(player->getName(), player -> getBalance());
    sleep_for(milliseconds(2000));    

    while(player_offer == false){
        this->graphicModule->clear();
        this->graphicModule->println("Faça sua aposta:", 25, true, false);
        offer = inputModule->readInt("");
        player_offer = DoOffer(offer);
    }

    GenerateCard(playercard);
    this->graphicModule->println("Aqui está sua cartela", 25, true, false);

    printCard(playercard);

    sleep_for(milliseconds(2000));    

    while((verificarCartelaCompleta(playercard) == false) ){
        int aux_cont = 0;
        int ramdomnumber = 0;
        while(ramdomnumber == 0 && player_lose == false){
            ramdomnumber = makedraw(old_numbers);
            aux_cont++;
            if(aux_cont> 76){
                aux_cont = 0;
                this->graphicModule->println("BINGO FINALIZADO", 25, true, false);
                sleep_for(milliseconds(1000));   
                player_lose = true;
            }
        }
        old_numbers.push_back(ramdomnumber);

        if(ramdomnumber == 0){
                player_lose = true;
        }
        if(!player_lose){
            this->graphicModule->print("Numero sorteado: " + std::to_string(ramdomnumber), 30, true, false);

            sleep_for(milliseconds(1000));      

            ValidatePlayerCard(ramdomnumber, playercard);
        }   
        if(HasCommonNumber(playercard,old_numbers) || player_lose){
            this->graphicModule->println("YOU LOSE!!!", 25, true, false);
            this->graphicModule->println("A  CARTELA NÃO FOI COMPLETADA", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance - offer);
            final_balance = player -> getBalance();
            this->graphicModule->print("Saldo Atual: ", 40, false, false);
            this->graphicModule->println("R$ " + std::to_string(final_balance), 80, true, false);
            sleep_for(milliseconds(2000));    
            this->graphicModule->clear();
            return;
        }
        this->graphicModule->clear();
    }

    if(verificarCartelaCompleta(playercard)){
            this->graphicModule->println("YOU WIN!!!", 25, true, false);
            int final_balance = player -> getBalance();
            player ->setBalance(final_balance + offer);
            final_balance = player -> getBalance();
            this->graphicModule->print("Saldo Atual: ", 80, false, false);
            this->graphicModule->println("R$ " + std::to_string(final_balance), 80, true, false);
            sleep_for(milliseconds(2000));    
            this->graphicModule->clear();
            return;
    }
}   