#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../blackjack_hpp/blackJack.hpp"

using std::cin;
using std::rand;
using std::string;
using std::to_string;
using std::vector;

BlackJack::BlackJack(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name, double minimumBet) : Game(graphicModule, randomNumberGenerator, inputModule, name, minimumBet) {}

void BlackJack::initiateCards()
{
    vector<int> cards = {};
    for (int i = 1; i < 14; i++)
    {
        cards.push_back(i);
    }
    for (int i = 0; i < 4; i++)
    {
        this->cards.insert(this->cards.end(), cards.begin(), cards.end());
    }
};

void BlackJack::initiateSuits()
{
    vector<string> spade = generateSuitvector("♠");
    vector<string> hearts = generateSuitvector("♥");
    vector<string> diamond = generateSuitvector("♦");
    vector<string> club = generateSuitvector("♣");
    this->suits.insert(this->suits.end(), spade.begin(), spade.end());
    this->suits.insert(this->suits.end(), hearts.begin(), hearts.end());
    this->suits.insert(this->suits.end(), diamond.begin(), diamond.end());
    this->suits.insert(this->suits.end(), club.begin(), club.end());
};

vector<string> BlackJack::generateSuitvector(string suit)
{
    vector<string> suits = {};
    for (int i = 0; i < 13; i++)
    {
        suits.push_back(suit);
    }
    return suits;
}

void BlackJack::play(Player *player)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initiateCards();
    initiateSuits();

    while (1)
    {
        this->graphicModule->clear();
        vector<int> currentCards = this->cards;
        vector<string> currentSuits = this->suits;
        bool newRound = true;
        bool gameIsOver = false;
        PlayerBlackjack house(2, "banca", true, 0);
        PlayerBlackjack playerBlackjack(player->getId(), player->getName(), true, player->getBalance());
        int option = 0;
        double aposta = 0;
        bool betSituation = false;
        this->graphicModule->clear();
        this->graphicModule->println("Jogador " + playerBlackjack.getName() + ", oque você deseja fazer?", 80, false, false);
        this->graphicModule->println("1. Jogar uma rodada", 80, false, false);
        this->graphicModule->println("2. Voltar ao menu principal", 80, false, false);
        this->graphicModule->println("3. Ler como jogar black jack", 80, false, false);

        option = this->inputModule->readInt("");
        if (option == 1)
        {
            while (!betSituation)
            {
                option = 0;
                this->graphicModule->clear();
                this->graphicModule->println("Seu saldo atual é de R$ " + to_string(playerBlackjack.getBalance()), 80, false, false);
                this->graphicModule->println("A aposta mínima é de R$ " + to_string(this->getMinimumBet()), 80, false, false);
                this->graphicModule->println("Qual será sua aposta?", 80, false, false);
                aposta = this->inputModule->readDouble("");
                betSituation = verifyBet(&aposta, player);
            }
            while (!gameIsOver)
            {
                if (playerBlackjack.getIsplaying())
                {

                    while (playerBlackjack.getIsplaying())
                    {
                        this->graphicModule->clear();
                        if (newRound == true)
                        {
                            playerBlackjack.setHand(generateHands(&currentCards, &currentSuits));
                            house.setHand(generateHands(&currentCards, &currentSuits));
                            newRound = false;
                        }
                        this->graphicModule->println("Jogador " + playerBlackjack.getName() + " sua mão vale " + to_string(playerBlackjack.getHand()->calculateHand()) + " , suas cartas são:", 80, false, false);
                        printCards(playerBlackjack);

                        this->graphicModule->println("1. Pedir por uma nova carta", 80, false, false);
                        this->graphicModule->println("2. Parar de jogar", 80, false, false);

                        option = this->inputModule->readInt("");
                        if (option == 1)
                        {
                            Hand newhand = getNewcard(&currentCards, &currentSuits);
                            playerBlackjack.insertNewcard(newhand.getCards()[0], newhand.getSuits()[0]);
                        }
                        else if (option == 2)
                        {
                            playerBlackjack.setIsplaying(false);
                        }
                        if (playerBlackjack.getHand()->calculateHand() > 21)
                        {
                            this->graphicModule->clear();
                            this->graphicModule->println("Sua mão estourou, suas cartas eram: ", 80, false, false);
                            printCards(playerBlackjack);
                            playerBlackjack.setIsplaying(false);
                            house.setIsplaying(false);
                        }
                        option = 0;
                    }
                }
                else if (house.getIsplaying())
                {
                    this->graphicModule->clear();
                    while (house.getIsplaying())
                    {
                        this->graphicModule->println("E a vez da casa jogar", 80, false, false);
                        analyzeNextPlay(&playerBlackjack, &house);
                        if (analyzeNextPlay(&playerBlackjack, &house))
                        {
                            Hand newhand = getNewcard(&currentCards, &currentSuits);
                            house.insertNewcard(newhand.getCards()[0], newhand.getSuits()[0]);
                        }
                        else
                        {
                            house.setIsplaying(false);
                        }
                        if (house.getHand()->calculateHand() > 21)
                        {
                            house.setIsplaying(false);
                        }
                        while (option != 1)
                        {
                            this->graphicModule->println("As cartas da casa são:", 80, false, false);
                            printCards(house);
                            this->graphicModule->println("Pressione 1 para continuar", 80, false, false);
                            option = this->inputModule->readInt("");
                            this->graphicModule->clear();
                        }
                    }
                }
                else
                {
                    option = 0;
                    if (playerBlackjack.getHand()->calculateHand() > 21)
                    {
                        while (option != 1)
                        {
                            gameIsOver = true;
                            player->setBalance(player->getBalance() - aposta);
                            playerBlackjack.setBalance(playerBlackjack.getBalance() - aposta);
                            this->graphicModule->println("Seu novo saldo é de R$ " + to_string(playerBlackjack.getBalance()), 80, false, false);
                            this->graphicModule->println("Essa rodada acabou", 80, false, false);

                            this->graphicModule->println("Pressione 1 para voltar", 80, false, false);
                            option = this->inputModule->readInt("");
                            this->graphicModule->clear();
                        }
                    }
                    else
                    {
                        while (option != 1)
                        {
                            this->graphicModule->println("Análise  dos resultados", 80, false, false);
                            this->graphicModule->println("Valor da mão do jogador " + to_string(playerBlackjack.getHand()->calculateHand()) + ".", 80, false, false);
                            this->graphicModule->println("As cartas do jogador " + playerBlackjack.getName() + " eram: ", 80, false, false);
                            ;
                            printCards(playerBlackjack);
                            this->graphicModule->println("Valor da mão do casa " + to_string(house.getHand()->calculateHand()), 80, false, false);
                            this->graphicModule->println("As cartas da casa eram : ", 80, false, false);
                            printCards(house);

                            this->graphicModule->println("O jodador " + analyzeWhoWon(&playerBlackjack, &house)->getName() + " ganhou", 80, false, false);
                            gameIsOver = true;
                            if (analyzeWhoWon(&playerBlackjack, &house)->getId() == 1)
                            {
                                player->setBalance(player->getBalance() + (2 * aposta));
                                playerBlackjack.setBalance(playerBlackjack.getBalance() + (2 * aposta));
                            }
                            else
                            {
                                player->setBalance(player->getBalance() - aposta);
                                playerBlackjack.setBalance(playerBlackjack.getBalance() - aposta);
                            }
                            while (option != 1)
                            {
                                this->graphicModule->println("Seu novo saldo é de R$ " + to_string(playerBlackjack.getBalance()), 80, false, false);
                                this->graphicModule->println("Essa rodada acabou", 80, false, false);

                                this->graphicModule->println("Pressione 1 para voltar", 80, false, false);
                                option = this->inputModule->readInt("");
                                this->graphicModule->clear();
                            }
                        }
                    }
                    if (player->getBalance() <= 0)
                    {
                        return;
                    }
                }
            }
        }
        else if (option == 3)
        {
            while (option != 1)
            {
                this->graphicModule->clear();
                this->graphicModule->println("Como jogar:", 80, false, false);
                this->graphicModule->println("Serão distribuídas 4 cartas 2 para o jogador e 2 para a casa.", 80, false, false);
                this->graphicModule->println("Então será a vez do jogador jogar ele pode escolher entre duas acoes,", 80, false, false);
                this->graphicModule->println("Pedir uma carta ou parar de jogar. Caso o valor das cartas do jogador ultrapasse", 80, false, false);
                this->graphicModule->println("o valor de 21 considerando as cartas J, Q e K valendo 10 o jogador automaticamente perderá", 80, false, false);
                this->graphicModule->println("o jogo. Caso o jogador decida parar de jogar então sera a vez da casa ate que ela decida", 80, false, false);
                this->graphicModule->println("parar de pedir cartas. Ao final ganha quem estiver mais próximo de 21 e não tiver ultrapassado", 80, false, false);
                this->graphicModule->println("esse valor.", 80, false, false);

                this->graphicModule->println("Pressione 1 para voltar", 80, false, false);
                option = this->inputModule->readInt("");
            }
        }
        else
        {
            this->graphicModule->clear();
            return;
        }
    }
};

Hand *BlackJack::generateHands(vector<int> *cards, vector<string> *suits)
{
    vector<int> handCards;
    vector<string> handSuits;
    for (size_t i = 0; i < 2; i++)
    {
        int numEle = verifynumElements(cards) - 1;
        int j = rand() % numEle;
        handCards.push_back((*cards)[j]);
        handSuits.push_back((*suits)[j]);
        (*cards).erase((*cards).begin() + j);
        (*suits).erase((*suits).begin() + j);
    }

    Hand *hand = new Hand(handCards, handSuits);
    return hand;
};
Hand BlackJack::getNewcard(vector<int> *cards, vector<string> *suits)
{
    vector<int> handCards;
    vector<string> handSuits;
    int numEle = verifynumElements(cards) - 1;
    int j = rand() % numEle;
    handCards.push_back((*cards)[j]);
    handSuits.push_back((*suits)[j]);
    (*cards).erase((*cards).begin() + j);
    (*suits).erase((*suits).begin() + j);
    Hand hand(handCards, handSuits);
    return hand;
}
int BlackJack::verifynumElements(vector<int> vector)
{
    int j = 0;
    for (auto i : vector)
    {
        j++;
    }
    return j;
};

int BlackJack::verifynumElements(vector<string> vector)
{
    int j = 0;
    for (auto i : vector)
    {
        j++;
    }
    return j;
};

int BlackJack::verifynumElements(vector<int> *vector)
{
    int j = 0;
    for (auto i : *vector)
    {
        j++;
    }
    return j;
};

int BlackJack::verifynumElements(vector<string> *vector)
{
    int j = 0;
    for (auto i : *vector)
    {
        j++;
    }
    return j;
};
void BlackJack::printCards(PlayerBlackjack player)
{
    for (int i = 0; i < verifynumElements(player.getHand()->getCards()); i++)
    {
        this->graphicModule->print(verifyCard(player.getHand()->getCards()[i]) + player.getHand()->getSuits()[i], 80, false, false);
        if (i == (verifynumElements(player.getHand()->getCards()) - 1))
        {
            this->graphicModule->println("", 80, false, false);
        }
        else
        {
            this->graphicModule->print(", ", 80, false, false);
        }
    }
}
string BlackJack::verifyCard(int card)
{
    if (card == 1 || card > 10)
    {
        switch (card)
        {
        case 1:
            return "A";
            break;
        case 11:
            return "J";
            break;
        case 12:
            return "Q";
            break;
        case 13:
            return "K";
            break;

        default:
            break;
        }
    }
    return to_string(card);
}

bool BlackJack::analyzeNextPlay(PlayerBlackjack *playerBlackjack, PlayerBlackjack *house)
{
    if (playerBlackjack->getHand()->calculateHand() > house->getHand()->calculateHand())
    {
        return true;
    }
    else
    {
        return false;
    }
}

PlayerBlackjack *BlackJack::analyzeWhoWon(PlayerBlackjack *playerBlackjack, PlayerBlackjack *house)
{

    if (playerBlackjack->getHand()->calculateHand() > house->getHand()->calculateHand())
    {
        if (playerBlackjack->getHand()->calculateHand() > 21)
        {
            return house;
        }
        else
        {
            return playerBlackjack;
        }
    }
    else
    {
        if (house->getHand()->calculateHand() > 21)
        {
            return playerBlackjack;
        }
        else
        {
            return house;
        }
    }
}

bool BlackJack::verifyBet(double *aposta, Player *player)
{
    int option = 0;
    if (*aposta <= 0.0 || *aposta > player->getBalance() || *aposta < this->getMinimumBet())
    {
        while (option != 1)
        {
            this->graphicModule->clear();
            this->graphicModule->println("Sua aposta é invalida. Insira um valor valido.", 80, false, false);
            this->graphicModule->println("Pressione 1 para realizar uma nova aposta", 80, false, false);
            option = this->inputModule->readInt("");
        }
        aposta = 0;
        return false;
    }
    else
    {
        return true;
    }
}