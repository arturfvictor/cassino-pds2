#ifndef CORE
#define CORE
#include <vector>
#include <string>
#include "playerBlackjack.hpp"
#include "../../hpp/Game.hpp"
#include "hand.hpp"
using std::string;
using std::vector;

class BlackJack : public Game {
    private:
    vector<int> cards;
    vector<string> suits;

    public:
    BlackJack(GraphicModule* graphicModule, RandomNumberGenerator* randomNumberGenerator, InputModule* inputModule, string name);
    void initiateCards();
    void initiateSuits();
    vector<string> generateSuitvector(string suit);
    void play(Player* player) override;
    Hand* generateHands(vector<int>* cards, vector<string>* suits);
    Hand getNewcard(vector<int>* cards, vector<string>* suits);
    int verifynumElements(vector<int> vector);
    int verifynumElements(vector<int>* vector);
    int verifynumElements(vector<string> vector);
    int verifynumElements(vector<string>* vector);
    void printCards(PlayerBlackjack player);
    string verifyCard(int card);
    void clear();
    bool analyzeNextPlay(PlayerBlackjack* player1,PlayerBlackjack* house);
    PlayerBlackjack* analyzeWhoWon(PlayerBlackjack* player1,PlayerBlackjack* house);

};
#endif