#include "../hpp/Player.hpp"

Player::Player() {
};

Player::Player(int id, string name, double balance) {
    this->id = id;
    this->name = name;
    this->balance = balance;
}

void Player::setId(int id) {
    this->id = id;
}

int Player::getId() {
    return this->id;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return this->name;
}

void Player::setBalance(double balance) {
    this->balance = balance;
}

double Player::getBalance() {
    return this->balance;
}