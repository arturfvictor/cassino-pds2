#ifndef HAND
#define HAND
#include <vector>
#include <string>

using std::vector;
using std::string;

class Hand {
private:
    vector<int> cards;
    vector<string> suits;
public:
    Hand(vector<int> cards, vector<string> suits);
    vector<int> getCards();
    vector<string> getSuits();
    void insertCard(int card);
    void insertSuit(string suit);
    int calculateHand();
};
#endif
