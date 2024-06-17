#ifndef PLAYERDAO
#define PLAYERDAO

#include "./GenericDao.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"
#include "../../model/hpp/Player.hpp"

class PlayerDao : public GenericDao<Player> {
    public:
        PlayerDao();
};

#endif