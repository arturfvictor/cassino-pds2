#ifndef PLAYERDAO
#define PLAYERDAO

#include "./GenericDao.hpp"
#include "../../model/hpp/Player.hpp"

class PlayerDao : public GenericDao<Player> {
    public:
        PlayerDao();
};

#endif