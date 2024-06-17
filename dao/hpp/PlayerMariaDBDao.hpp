#ifndef PLAYERMARIADBDAO
#define PLAYERMARIADBDAO

#include <map>
#include <vector>

#include "./PlayerDao.hpp"

using std::map;
using std::vector;

class PlayerMariaDBDao : public PlayerDao {
    private:
        map<int, Player*> players;

    public:
        PlayerMariaDBDao();
        vector<Player*> list() override;
        Player* find(int id) override;
        Player* save(Player* object) override;
        Player* remove(int id) override;
};

#endif