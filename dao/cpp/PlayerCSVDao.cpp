#include "../hpp/PlayerCSVDao.hpp"
#include <fstream>
#include <sstream>

PlayerCSVDao::PlayerCSVDao(): PlayerDao() {
    std::ifstream file("../save.csv");

    if (file.is_open()) {
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
        playerMapDao.save(player);
    }
}

vector<Player*> PlayerCSVDao::list() {
    return playerMapDao.list();
}

Player* PlayerCSVDao::find(int id) {
    return playerMapDao.find(id);
}

Player* PlayerCSVDao::save(Player* player) {
    playerMapDao.save(player);
    writeToFile();
    return player;
}

Player* PlayerCSVDao::remove(int id) {
    Player* player = playerMapDao.remove(id);
    writeToFile();
    return player;
}

void PlayerCSVDao::writeToFile() {
    fstream fout;

    fout.open("../save.csv", std::ios::out);
    fout << "id;name;balance\n";

    for (Player* player : playerMapDao.list()) {
        fout << std::to_string(player->getId()) << ";";
        fout << player->getName() << ";";
        fout << std::to_string(player->getBalance()) << ";\n";
    } 

    fout.close();
}