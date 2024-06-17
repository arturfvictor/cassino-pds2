#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/FilhoDaPuta.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./game/blackjack/blackjack_hpp/blackJack.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, double player);
// void loadPlayerContext(GraphicModule* graphicModule, InputModule* inputModule, RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao, Player* player);
// int generateUniqueId(PlayerDao* playerDao, RandomNumberGenerator* randomNumberGenerator);
// Player* loadPlayer(GraphicModule* graphicModule, InputModule* inputModule, RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();
    FilhoDaPuta* playerDao = new FilhoDaPuta();
    Player* player;

    // loadPlayerContext(graphicModule, inputModule, randomNumberGenerator, playerDao, player);

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa", 50.0);
    Game* blackJack = new BlackJack(graphicModule, randomNumberGenerator, inputModule, "Black Jack", 50.0);

    vector<Game*> games;
    games.push_back(coinFlip);
    games.push_back(blackJack);

    while (true) {
        showGameMenu(graphicModule, games, player->getBalance());
        int gameId = inputModule->readIntInRange("", 0, games.size() - 1);
        games[gameId]->play(player);
    }
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, double balance) {
    graphicModule->print("Saldo Atual: ", 80, false, false);
    graphicModule->println("R$ " + std::to_string(balance), 80, true, false);
    graphicModule->println("Escolha um dos jogos:", 80, false, true);

    int pos = 0;
    for (auto game : games) {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 80, false, false);
        pos++;
    }
}

// void loadPlayerContext(GraphicModule* graphicModule, InputModule* inputModule, RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao, Player* player) {
//     graphicModule->println("Você deseja salvar sua pontuação?", 80, true, false);
//     graphicModule->println("0 - Sim", 80, true, false);
//     graphicModule->println("1 - Não", 80, true, false);

//     int res = inputModule->readIntInRange("", 0, 1);

//     if (res == 0) {
//         playerDao = new PlayerCSVDao();

//         player = loadPlayer(graphicModule, inputModule, randomNumberGenerator, playerDao);
//     } else if (res == 1) {
//         playerDao = new PlayerMapDao();
//     }
// }

// Player* loadPlayer(GraphicModule* graphicModule, InputModule* inputModule, RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao) {
//     graphicModule->println("Você deseja usar um save anterior?", 80, true, false);
//     graphicModule->println("0 - Sim", 80, true, false);
//     graphicModule->println("1 - Não", 80, true, false);

//     int res = inputModule->readIntInRange("", 0, 1);

//     if (res == 0) {
//         graphicModule->print("Insira o ID do save: ", 80, false, false);
//         int id = inputModule->readInt("");
//         Player* player = playerDao->find(id);

//         if (player != nullptr) {
//             return player;
//         }
//     }

//     string playerName = inputModule->readString("Insira seu nome: ");
//     return new Player(generateUniqueId(playerDao, randomNumberGenerator), playerName, 500.0);
// }

// int generateUniqueId(PlayerDao* playerDao, RandomNumberGenerator* randomNumberGenerator) {
//     while (true) {
//         int id = randomNumberGenerator->generate();

//         if (playerDao->find(id) == nullptr) {
//             return id;
//         }
//     }
// }
