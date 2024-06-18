#include <iostream>
#include <string>
#include <vector>

#include "./dao/hpp/PlayerMapDao.hpp"
#include "./module/input-module/hpp/CommandLineInputModule.hpp"
#include "./module/graphic-module/hpp/CommandLineGraphicModule.hpp"
#include "./module/random-number-generator/hpp/BasicRandomNumberGenerator.hpp"
#include "./game/hpp/CoinFlipGame.hpp"
#include "./game/hpp/Dados.hpp"
#include "./game/hpp/BingoGame.hpp"
#include "./game/hpp/JogoDoBicho.hpp"
#include "./game/blackjack/blackjack_hpp/blackJack.hpp"
#include "./dao/hpp/GenericDao.hpp"
#include "./model/hpp/Player.hpp"

using std::cin;
using std::cout;
using std::endl;

void showGameMenu(GraphicModule *graphicModule, vector<Game *> games);

int main()
{
    GraphicModule *graphicModule = new CommandLineGraphicModule();
    InputModule *inputModule = new CommandLineInputModule(graphicModule);
    RandomNumberGenerator *randomNumberGenerator = new BasicRandomNumberGenerator();

    Player *p1 = new Player(1, "Player1", 500.0);

    Game *dados = new Dados(graphicModule, randomNumberGenerator, inputModule, "Dados", 50);
    Game *coinFlip = new CoinFlipGame(graphicModule, randomNumberGenerator, inputModule, "Cara ou Coroa", 50);
    Game *blackJack = new BlackJack(graphicModule, randomNumberGenerator, inputModule, "Black Jack", 10);
    Game *bicho = new JogoDoBicho(graphicModule, randomNumberGenerator, inputModule, "Jogo do Bicho", 120);
    Game *bingo = new BingoGame(graphicModule, randomNumberGenerator, inputModule, "Bingo", 70);

    vector<Game *> games;
    games.push_back(coinFlip);
    games.push_back(blackJack);
    games.push_back(bicho);
    games.push_back(bingo);
    games.push_back(dados);
    while (true)
    {
        if (p1->getBalance() <= 0)
        {
            int option = 0;
            while (option != 1)
            {
                graphicModule->println("Game Over", 10, true, true);
                graphicModule->println("Você perdeu, mais sorte na proxíma vez", 10, true, true);
                graphicModule->println("Pressione 1 para continuar", 80, false, false);
                cin >> option;
            }
            graphicModule->clear();
            return 0;
        }
        showGameMenu(graphicModule, games);
        int gameId = inputModule->readIntInRange("", 0, games.size() - 1);
        games[gameId]->play(p1);
    }
}

void showGameMenu(GraphicModule *graphicModule, vector<Game *> games)
{
    graphicModule->print("Escolha um dos jogos:\n", 25, false, true);
    int pos = 0;
    for (auto game : games)
    {
        graphicModule->println(std::to_string(pos) + " - " + game->getName(), 25, false, false);
        pos++;
    }
}