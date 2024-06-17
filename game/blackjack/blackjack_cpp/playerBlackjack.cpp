#include <vector>
#include <string>
#include "../blackjack_hpp/playerBlackjack.hpp"
#include "../../../dao/hpp/PlayerDao.hpp"
using std::string;
using std::vector;

PlayerBlackjack::PlayerBlackjack(int id, string name, bool isplaying, float balance) : id(id), name(name), isplaying(isplaying), balance(balance){};

int PlayerBlackjack::getId()
{
    return this->id;
};

string PlayerBlackjack::getName()
{
    return this->name;
};

bool PlayerBlackjack::getIsplaying()
{
    return this->isplaying;
};

Hand *PlayerBlackjack::getHand()
{
    return this->hand;
};
float PlayerBlackjack::getBalance()
{
    return this->balance;
}
void PlayerBlackjack::setHand(Hand *hand)
{
    this->hand = hand;
}

void PlayerBlackjack::setIsplaying(bool status)
{
    this->isplaying = status;
};

void PlayerBlackjack::setBalance(float balance)
{
    this->balance = balance;
};

 void PlayerBlackjack::insertNewcard(int card, string suit){
    this->hand->insertCard(card);
    this->hand->insertSuit(suit);
 };
