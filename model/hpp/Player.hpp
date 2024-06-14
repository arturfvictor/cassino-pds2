#ifndef PLAYER
#define PLAYER

#include <string>

using std::string;

class Player {
    private:
        int id;
        string name;
        float balance;

    public:
        Player();
        Player(int id, string name, float balance);

        void setId(int id);
        int getId();

        void setName(string name);
        string getName();

        void setBalance(float balance);
        float getBalance();
};

#endif