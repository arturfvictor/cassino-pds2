#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./dao/hpp/PlayerCSVDao.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./game/blackjack/blackjack_hpp/blackJack.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, string name, double balance);
int generateUniqueId(RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();
    PlayerDao* playerDao = new PlayerCSVDao();

    Player* player = nullptr;

    graphicModule->println("Você deseja usar um save anterior?", 80, true, false);
    graphicModule->println("0 - Sim", 80, true, false);
    graphicModule->println("1 - Não", 80, true, false);

    int res = inputModule->readIntInRange("", 0, 1);

    if (res == 0) {
        graphicModule->print("Insira o ID do save: ", 80, false, false);
        int id = inputModule->readInt("");

        Player* playerOnDB = playerDao->find(id);

        if (playerOnDB != nullptr) {
            player = playerOnDB;
        } else {
            graphicModule->println("Save não encontrado!", 80, true, false);
            graphicModule->print("Insira seu nome: ", 80, false, false);
            string playerName = inputModule->readString("");

            player = new Player(
                generateUniqueId(randomNumberGenerator, playerDao),
                playerName,
                500.0
            );
            playerDao->save(player);
        }
    } else {
        graphicModule->print("Insira seu nome: ", 80, false, false);
        string playerName = inputModule->readString("");

        player = new Player(
            generateUniqueId(randomNumberGenerator, playerDao),
            playerName,
            500.0
        );
        playerDao->save(player);
    }

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa", 50.0);
    Game* blackJack = new BlackJack(graphicModule, randomNumberGenerator, inputModule, "Black Jack", 50.0);

    vector<Game*> games;
    games.push_back(coinFlip);
    games.push_back(blackJack);

    while (true) {
        showGameMenu(graphicModule, games, player->getName(), player->getBalance());
        int gameId = inputModule->readIntInRange("", 0, games.size() - 1);
        games[gameId]->play(player);
        playerDao->save(player); // Saving player object after every round
    }
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, string name, double balance) {
    graphicModule->print("Olá, ", 80, false, false);
    graphicModule->println(name, 80, true, false);
    graphicModule->print("Saldo Atual: ", 80, false, false);
    graphicModule->println("R$ " + std::to_string(balance), 80, true, false);
    graphicModule->println("Escolha um dos jogos:", 80, false, true);

    int pos = 0;
    for (auto game : games) {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 80, false, false);
        pos++;
    }
}

int generateUniqueId(RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao) {
    while (true) {
        int id = randomNumberGenerator->generate();

        if (playerDao->find(id) == nullptr) {
            printf("%d", id);
            return id;
        }
    }
}