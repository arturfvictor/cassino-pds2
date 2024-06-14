#ifndef PLAYERMAPDAO
#define PLAYERMAPDAO

#include <map>
#include <vector>

#include "./PlayerDao.hpp"

using std::map;
using std::vector;

class PlayerMapDao : public PlayerDao {
    private:
        map<int, Player*> players;

    public:
        PlayerMapDao();
        vector<Player*> list() override;
        Player* find(int id) override;
        Player* save(Player* object) override;
        Player* remove(int id) override;
};

#endif