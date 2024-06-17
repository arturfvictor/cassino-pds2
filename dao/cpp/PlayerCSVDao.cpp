#include <fstream>
#include <sstream>
#include <string>

#include "../hpp/PlayerCSVDao.hpp"
#include "../../module/random-number-generator/hpp/RandomNumberGenerator.hpp"

PlayerCSVDao::PlayerCSVDao(): PlayerDao() {
    std::ifstream file("../save.csv");

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open save.csv");
    }

    string line;
    getline(file, line);

    while(getline(file, line)) {
        std::stringstream sstream(line);

        vector<string> info;

        while(sstream.good()) {
            string substring;
            getline(sstream, substring, ';');
            info.push_back(substring);
        }

        Player* player = new Player(
            stoi(info[0]),
            info[1],
            stod(info[2])
        );
        players.push_back(player);
    }
}

vector<Player*> PlayerCSVDao::list() {
    return players;
}

Player* PlayerCSVDao::find(int id) {
    for (Player* player : players) {
        if (player->getId() == id) {
            return player;
        }
    }
    return nullptr;
}

Player* PlayerCSVDao::save(Player* player) {
    if (find(player->getId()) != nullptr) {
        remove(player->getId());
    }
    players.push_back(player);

    writeToFile();
    return player;
}

Player* PlayerCSVDao::remove(int id) {
    Player* player = nullptr;

    vector<Player*>::iterator it = players.begin();
    for (auto item : players) {
        if (item->getId() == id) {
            player = item;
            players.erase(it);
            break;
        }
        it++;
    } 

    writeToFile();
    return player;
}

void PlayerCSVDao::writeToFile() {
    fstream fout;

    fout.open("../save.csv", std::ios::out);
    fout << "id;name;balance\n";

    for (Player* player : list()) {
        fout << std::to_string(player->getId()) << ";";
        fout << player->getName() << ";";
        fout << std::to_string(player->getBalance()) << ";\n";
    } 

    fout.close();
}