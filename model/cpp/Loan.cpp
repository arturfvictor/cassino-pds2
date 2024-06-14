#include "../hpp/Loan.hpp"

Loan::Loan() {
}

Loan::Loan(float amount, int totalRounds): amount(amount), totalRounds(totalRounds) {
}

void Loan::setAmount(float amount) {
    this->amount = amount;
}

float Loan::getAmount() {
    return this->amount;
}

void Loan::setTotalRounds(int totalRounds){
    this->totalRounds = totalRounds;
}

int Loan::getTotalRounds() {
    return this->totalRounds;
}

void Loan::setRemainingRounds(int remainingRounds) {
    this->remainingRounds = remainingRounds;
}

int Loan::getRemainingRounds() {
    return this->remainingRounds;
}