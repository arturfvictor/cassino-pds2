#include "../hpp/PlayerMapDao.hpp"

PlayerMapDao::PlayerMapDao(): PlayerDao() {
}

vector<Player*> PlayerMapDao::list() {
    map<int, Player*>::iterator it = players.begin();

    vector<Player*> playerVector;
    while (it != players.end()) {
        playerVector.push_back(it->second);
        it++;
    }

    return playerVector;
}

Player* PlayerMapDao::find(int id) {
    map<int, Player*>::iterator it = players.find(id);
    if (it == players.end()) {
        return nullptr;
    } else {
        return it->second;
    }
}

Player* PlayerMapDao::save(Player* player) {
    players[player->getId()] = player;
    return player;
}

Player* PlayerMapDao::remove(int id) {
    Player* player = find(id);
    players.erase(id);
    return player;
}