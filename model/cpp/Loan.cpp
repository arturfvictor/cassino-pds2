#include "../hpp/Loan.hpp"

Loan::Loan() {
}

Loan::Loan(double amount, int totalRounds): amount(amount), totalRounds(totalRounds) {
}

void Loan::setAmount(double amount) {
    this->amount = amount;
}

double Loan::getAmount() {
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