#ifndef LOAN
#define LOAN

class Loan {
    private:
        float amount;
        int totalRounds;
        int remainingRounds;

    public:
        Loan();
        Loan(float amount, int totalRounds);

        void setAmount(float amount);
        float getAmount();

        void setTotalRounds(int totalRounds);
        int getTotalRounds();

        void setRemainingRounds(int remainingRounds);
        int getRemainingRounds();
};

#endif