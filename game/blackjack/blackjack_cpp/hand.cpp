#include <vector>
#include <string>
#include "../blackjack_hpp/hand.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::vector;

Hand::Hand(vector<int> cards, vector<string> suits) : cards(cards), suits(suits){};

vector<int> Hand::getCards()
{
    return this->cards;
};

vector<string> Hand::getSuits()
{
    return this->suits;
};

void Hand::insertCard(int card)
{
    this->cards.push_back(card);
};

void Hand::insertSuit(string suit) {
    this->suits.push_back(suit);
};

int Hand::calculateHand(){
    int value = 0;
    for (auto i: cards){
        if(i>10){
            value = value+10;
        }else{
           value = value + i;
        }
    }
    return value;
}
