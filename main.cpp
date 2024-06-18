#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./dao/hpp/PlayerCSVDao.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./game/hpp/Dados.hpp"
#include "./game/hpp/BingoGame.hpp"
#include "./game/hpp/JogoDoBicho.hpp"
#include "./game/blackjack/blackjack_hpp/blackJack.hpp"
#include "./model/hpp/Player.hpp"

using std::cout;
using std::endl;

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, Player* player);
int generateUniqueId(RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao);

int main() {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator* randomNumberGenerator = new BasicRandomNumberGenerator();
    PlayerDao* playerDao = new PlayerCSVDao();

    Player* player = nullptr;

    graphicModule->println("Você deseja usar um save anterior?", 80, true, false);
    graphicModule->println("1 - Sim", 80, true, false);
    graphicModule->println("2 - Não", 80, true, false);

    int res = inputModule->readIntInRange("", 1, 2);

    if (res == 1) {
        graphicModule->print("Insira o ID do save: ", 80, false, false);
        int id = inputModule->readInt("");

        Player* playerOnDB = playerDao->find(id);

        if (playerOnDB != nullptr) {
            player = playerOnDB;
        } else {
            graphicModule->println("Save não encontrado!", 80, true, false);
            graphicModule->print("Insira seu nome:", 80, false, false);
            string playerName = inputModule->readString("");

            player = new Player(
                generateUniqueId(randomNumberGenerator, playerDao),
                playerName,
                500.0
            );
            playerDao->save(player);
        }
    } else {
        graphicModule->print("Insira seu nome:", 80, false, false);
        string playerName = inputModule->readString("");

        player = new Player(
            generateUniqueId(randomNumberGenerator, playerDao),
            playerName,
            1500.0
        );
        playerDao->save(player);
    }

    Game* coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa", 50.0);
    Game* blackJack = new BlackJack(graphicModule, randomNumberGenerator, inputModule, "Black Jack", 100.0);
    Game* bicho = new JogoDoBicho(graphicModule, randomNumberGenerator, inputModule, "Jogo do Bicho", 120);
    Game* bingo = new BingoGame(graphicModule, randomNumberGenerator, inputModule, "Bingo", 70.0);
    Game* dados = new Dados(graphicModule, randomNumberGenerator, inputModule, "Dados", 50.0);

    vector<Game *> games;
    games.push_back(coinFlip);
    games.push_back(blackJack);
    games.push_back(bicho);
    games.push_back(bingo);
    games.push_back(dados);

    while (true) {
        showGameMenu(graphicModule, games, player);
        int gameId = inputModule->readIntInRange("", 1, games.size());
        games[gameId-1]->play(player);
        playerDao->save(player); // Saving player object after every round

        if (player->getBalance() <= 0) {
            graphicModule->println("Game Over", 10, true, true);
            graphicModule->println("Você perdeu, mais sorte na proxíma vez", 10, true, true);
            graphicModule->println("Pressione 1 para continuar", 80, false, false);

            inputModule->readIntInRange("", 1, 1);

            graphicModule->clear();
            return 0;
        }
    }
}

void showGameMenu(GraphicModule* graphicModule, vector<Game*> games, Player* player) {
    graphicModule->print("Olá, ", 80, false, false);
    graphicModule->println(player->getName() + " (" + std::to_string(player->getId()) + ")", 80, true, false);
    graphicModule->print("Saldo Atual: ", 80, false, false);
    graphicModule->println("R$ " + std::to_string(player->getBalance()), 80, true, false);
    graphicModule->println("Escolha um dos jogos:", 80, false, true);

    int pos = 1;
    for (auto game : games)
    {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 25, false, false);
        pos++;
    }
}

int generateUniqueId(RandomNumberGenerator* randomNumberGenerator, PlayerDao* playerDao) {
    while (true) {
        int id = randomNumberGenerator->generate();

        if (playerDao->find(id) == nullptr) {
            return id;
        }
    }
}