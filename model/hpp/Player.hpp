#ifndef PLAYER
#define PLAYER

#include <string>

using std::string;

class Player {
    private:
        int id;
        string name;
        double balance;

    public:
        Player();
        Player(int id, string name, double balance);

        void setId(int id);
        int getId();

        void setName(string name);
        string getName();

        void setBalance(double balance);
        double getBalance();
};

#endif