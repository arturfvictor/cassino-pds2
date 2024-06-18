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

BingoGame::BingoGame(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name, double minimum_bet) : Game(graphicModule, randomNumberGenerator, inputModule, name, minimum_bet) {}

/**
 * @brief Gera um numero randomico não repetido
 *
 * @param numbers vector de int de numeros usados em sorteios anteriores
 * @return int numero aleatorio não repetido
 */
int BingoGame::makedraw(std::vector<int> &numbers)
{
    int number;
    number = this->randomNumberGenerator->generate(1, 76);
    for (int num : numbers)
    {
        if (num == number)
        {
            return 0;
        }
    }
    return number;
}
/**
 * @brief verifica o input do jogador como uma resposta válida
 *
 * @param input string da resposta do jogador
 * @return true se for uma resposta valida
 * @return false se não for uma respota valida
 */
bool BingoGame::ValidateConfirmation(string input)
{
    if (input == "S" || input == "s" || input == "sim" || input == "N" || input == "n" || input == "nao" || input == "não")
    {
        return true;
    }
    this->graphicModule->clear();
    this->graphicModule->print("Opção inválida, tente novamente!", 25, true, false);
    sleep_for(milliseconds(500));
    return false;
}

/**
 * @brief gera uma cartela para o jogador com numeros aleatórios
 *
 * @param cartela vector de int dos numeros da cartela
 */
void BingoGame::GenerateCard(std::vector<int> &cartela)
{
    std::vector<int> uniqueNumbers;
    cartela.resize(25);
    for (int i = 0; i < 25; ++i)
    {
        int num;
        do
        {
            num = randomNumberGenerator->generate(1, 76);
        } while (std::find(uniqueNumbers.begin(), uniqueNumbers.end(), num) != uniqueNumbers.end());

        uniqueNumbers.push_back(num);
        cartela[i] = num;
    }
}
/**
 * @brief printa a cartela para o jogador com as divisões e a marcações
 *
 * @param cartela vector de int dos numeros da cartela
 */
void BingoGame::printCard(const std::vector<int> &cartela)
{
    this->graphicModule->println("", 25, false, false);
    for (int i = 0; i < cartela.size(); ++i)
    {
        if (cartela[i] == 0)
        {
            this->graphicModule->print("X", 80, false, false);
        }
        else
        {
            this->graphicModule->print(std::to_string(cartela[i]), 80, false, true);
        }
        if ((i + 1) % 5 != 0)
        {
            this->graphicModule->print(" | ", 80, false, false);
        }
        else
        {
            this->graphicModule->println("", 25, false, false);
        }
    }
}

/**
 * @brief recebe os inputs do jogador para validar se o numero realmente está na cartela
 *
 * @param ramdomnumber numero sorteado
 * @param cartela vector de int da cartela
 */
void BingoGame::ValidatePlayerCard(int ramdomnumber, std::vector<int> &cartela)
{

    string char_input;

    bool validation = false;
    while (validation == false)
    {
        this->graphicModule->clear();
        this->graphicModule->print("O numero " + std::to_string(ramdomnumber) + " está na sua cartela? ", 70, false, false);
        this->graphicModule->println("", 25, false, false);
        printCard(cartela);
        char_input = inputModule->readString("");
        validation = ValidateConfirmation(char_input);
        this->graphicModule->clear();
    }
    if (validation == true)
    {
        if (char_input == "sim" || char_input == "S" || char_input == "s")
        {
            this->graphicModule->println("digite o numero: ", 80, false, false);
            int card_number;
            card_number = inputModule->readInt("");
            if (card_number == ramdomnumber)
            {
                if (MarkPlayerCard(cartela, card_number) == true)
                {
                    this->graphicModule->print("Número " + std::to_string(card_number) + " marcado na cartela.", 80, false, false);
                    printCard(cartela);
                    sleep_for(milliseconds(1000));
                }
                else
                {
                    this->graphicModule->println("Número não está na sua cartela.", 80, false, false);
                    printCard(cartela);

                    sleep_for(milliseconds(1000));
                }
            }else{
                this->graphicModule->println("VOCÊ MARCOU O NUMERO INCORRETO NA CARTELA", 30, false, false);
            }
        }
    }
    else
    {

        return;
    }
}

/**
 * @brief verifica se toda a cartela foi marcada
 *
 * @param cartela recebe o vetor dos numeros da cartela
 * @return true se foi completamente marcada
 * @return false se ainda não foram marcados todos os numeros
 */
bool BingoGame ::verificarCartelaCompleta(const std::vector<int> &cartela)
{
    for (int num : cartela)
    {
        if (num != 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief verifica se a aposta do jogador condiz com o valor minimo
 *
 * @param offer valor apostado do jogador
 * @return true se for maior retorna true
 * @return false se for menor que o minimo retorna false
 */
bool BingoGame::DoOffer(int offer)
{

    if (offer < 70)
    {
        this->graphicModule->println("Aposta insuficiente", 25, true, false);
        sleep_for(milliseconds(500));
        return false;
    }
    else
    {
        return true;
    }
}
/**
 * @brief Verifica se na cartela do jogador há algum numero que ja foi sorteado
 *
 * @param cartela vector de int da cartela do jogador
 * @param old_numbers vector de int dos numeros sorteados anteriormente
 * @return true se há algum numero não nulo igual nas duas cartelas
 * @return false se não há algum numero não nulo igual nas duas cartelas
 */
bool BingoGame::HasCommonNumber(const std::vector<int> &cartela, const std::vector<int> &old_numbers)
{
    for (const int &num_cartela : cartela)
    {
        for (const int &num_old : old_numbers)
        {
            if ((num_cartela == num_old) && num_cartela != 0)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Marca na cartela o valor selecionado
 *
 * @param card vector de int dos numeros da cartela do jogador
 * @param number numero a ser marcado
 * @return true se existe um numero number na cartela card
 * @return false se não existe um numero number na cartela card
 */
bool BingoGame::MarkPlayerCard(std::vector<int> &card, int number)
{
    bool mark = false;
    for (int i = 0; i < card.size(); ++i)
    {
        if (card[i] == number)
        {
            card[i] = 0; // Marca o número com 0
            mark = true;
            break; // Encerra
        }
    }
    return mark;
}
/**
 * @brief Função de controle das ações do jogo
 *
 * @param player jogador
 */
void BingoGame::play(Player *player)
{

    // Variaveis globais
    std::vector<int> playercard(5);
    std::vector<int> old_numbers(76);

    bool player_offer = false;
    bool player_lose = false;
    int offer;

    showGameHeader(player->getName(), player->getBalance());

    sleep_for(milliseconds(2000));

    // Enquanto o jogador não fizer sua aposta
    while (player_offer == false)
    {
        this->graphicModule->clear();
        this->graphicModule->println("Faça sua aposta:", 25, true, false);
        offer = inputModule->readInt("");
        // Valida a aposta do jogador
        player_offer = DoOffer(offer);
    }

    // gera a cartela para o inicio do jogo
    GenerateCard(playercard);
    this->graphicModule->println("Aqui está sua cartela", 25, true, false);
    printCard(playercard);

    sleep_for(milliseconds(2000));

    // Roda o jogo enquanto o player não vencer
    while ((verificarCartelaCompleta(playercard) == false))
    {

        int aux_cont = 0;
        int ramdomnumber = 0;

        // aguarda um retorno não nulo do sorteio
        while (ramdomnumber == 0 && player_lose == false)
        {
            ramdomnumber = makedraw(old_numbers);
            aux_cont++;
            // caso o sorteio tenha falhado mais que o numero maximo de numeros
            if (aux_cont > 76)
            {
                aux_cont = 0;
                this->graphicModule->println("BINGO FINALIZADO", 25, true, false);
                sleep_for(milliseconds(1000));
                // Aciona a flag de derrota do jogador
                player_lose = true;
            }
        }
        // Guarda no vetor de numeros antigos o numero sorteado
        old_numbers.push_back(ramdomnumber);

        // Verificação final do numero sorteado
        if (ramdomnumber == 0)
        {
            player_lose = true;
        }
        // Enquanto a flag não estiver ativa, permite o player jogar o jogo
        if (!player_lose)
        {
            this->graphicModule->print("Numero sorteado: " + std::to_string(ramdomnumber), 30, true, false);

            sleep_for(milliseconds(1000));

            ValidatePlayerCard(ramdomnumber, playercard);
        }
        // Se o jogador deixou de anotar algum numero, ou perdeu o jogo
        if (HasCommonNumber(playercard, old_numbers) || player_lose)
        {
            this->graphicModule->println("YOU LOSE!!!", 25, true, false);
            this->graphicModule->println("A  CARTELA NÃO FOI COMPLETADA", 25, true, false);
            int final_balance = player->getBalance();
            player->setBalance(final_balance - offer);
            final_balance = player->getBalance();
            this->graphicModule->print("Saldo Atual: ", 40, false, false);
            this->graphicModule->println("R$ " + std::to_string(final_balance), 80, true, false);
            sleep_for(milliseconds(2000));
            this->graphicModule->clear();
            return;
        }
        this->graphicModule->clear();
    }
    // Caso ele anotou todos os numeros corretamente
    if (verificarCartelaCompleta(playercard))
    {
        this->graphicModule->println("YOU WIN!!!", 25, true, false);
        int final_balance = player->getBalance();
        player->setBalance(final_balance + offer);
        final_balance = player->getBalance();
        this->graphicModule->print("Saldo Atual: ", 80, false, false);
        this->graphicModule->println("R$ " + std::to_string(final_balance), 80, true, false);
        sleep_for(milliseconds(2000));
        this->graphicModule->clear();
        return;
    }
}