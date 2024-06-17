#ifndef LOAN
#define LOAN

class Loan {
    private:
        double amount;
        int totalRounds;
        int remainingRounds;

    public:
        Loan();
        Loan(double amount, int totalRounds);

        void setAmount(double amount);
        double getAmount();

        void setTotalRounds(int totalRounds);
        int getTotalRounds();

        void setRemainingRounds(int remainingRounds);
        int getRemainingRounds();
};

#endif