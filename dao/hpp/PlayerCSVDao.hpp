#ifndef PLAYERCSVDAO
#define PLAYERCSVDAO

#include <map>
#include <vector>

#include "./PlayerMapDao.hpp"

using std::map;
using std::vector;
using std::fstream;

class PlayerCSVDao : public PlayerDao {
    private:
        PlayerMapDao playerMapDao;
        void writeToFile();

    public:
        PlayerCSVDao();
        vector<Player*> list() override;
        Player* find(int id) override;
        Player* save(Player* object) override;
        Player* remove(int id) override;
};

#endif