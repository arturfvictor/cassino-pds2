#include "JogoDoBicho.hpp"

JogoDoBicho::JogoDoBicho(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, std::string name, double minimumBet)
    : Game(graphicModule, randomNumberGenerator, inputModule, name, minimumBet),
      animais{
          {"Avestruz", 1},
          {"Águia", 2},
          {"Burro", 3},
          {"Borboleta", 4},
          {"Cachorro", 5},
          {"Cabra", 6},
          {"Carneiro", 7},
          {"Camelo", 8},
          {"Cobra", 9},
          {"Coelho", 10},
          {"Cavalo", 11},
          {"Elefante", 12},
          {"Galo", 13},
          {"Gato", 14},
          {"Jacaré", 15},
          {"Leão", 16},
          {"Macaco", 17},
          {"Porco", 18},
          {"Pavão", 19},
          {"Peru", 20},
          {"Touro", 21},
          {"Tigre", 22},
          {"Urso", 23},
          {"Veado", 24},
          {"Vaca", 25}},
      modosdeaposta{
          {"Animal"},
          {"Dezena"}}
{
    // O corpo do construtor pode estar vazio
}

void JogoDoBicho::play(Player *player)
{
float odd = 1;
    bool firstExec = true;
    bool inputValidation;

    showGameHeader(player->getName(), player->getBalance());

    this->graphicModule->clear();
    this->graphicModule->print("Escolha um modo de aposta:\n", 14, false, true); //"Escolha um animal para apostar:" << std::endl;
    int pos = 0;
    for (const auto &aposta : modosdeaposta)
    {
        string string_aux = aposta;
        this->graphicModule->println(std::to_string(pos) + " - " + string_aux, 10, false, true);
        pos++;
    }

    int NumbertipoSorteio = inputModule->readIntInRange("", 0, modosdeaposta.size() - 1);

    if (NumbertipoSorteio == 0)
    {
        tipoSorteio = "Animal";
        odd = 18;
    }
    else if (NumbertipoSorteio == 1)
    {
        tipoSorteio = "Dezena";
        odd = 80;
    }
    else
    {
        this->graphicModule->println("Opcao Invalida", 100, true, true);
    }
    this->graphicModule->println("Tipo Sorteio: " + tipoSorteio, 25, true, false);
    double bet = readBet(getMinimumBet(), player->getBalance());
    mostrarAnimal();
    string animalEscolhido = inputModule->readString(""); // Solicita a escolha do animal
    int numeroAnimal = escolherAnimal(animalEscolhido);
    // string tiposorteio = inputModule->readString("Iniciar Sorteio? Sim ou Nao: ");
    if (numeroAnimal != -1)
    {
        this->graphicModule->println("Número do animal escolhido: " + std::to_string(numeroAnimal), 25, true, false);
        string iniciarSorteio = inputModule->readString("Iniciar Sorteio? Sim ou Nao: ");
        if (iniciarSorteio == "Sim" || iniciarSorteio == "sim")
        {
            // Pergunta se é dezena ou animal
            // string tipoSorteio = inputModule->readString("Deseja sortear por Dezena ou Animal? ");
            this->graphicModule->println("Tipo Sorteio: " + tipoSorteio, 25, true, false);

            graphicModule->println("Sorteando........", 35, false, false);
            graphicModule->wait(750);
            graphicModule->clear();
            bool resultado = sorteio(tipoSorteio, numeroAnimal);
            if (resultado)
            {
                double balance = player->getBalance();
                player->setBalance(balance + (bet * odd));

                graphicModule->println("VOCE GANHOU " + std::to_string(bet) + "!", 80, true, false);
                graphicModule->println("Novo saldo: R$", 80, false, false);
                graphicModule->println(std::to_string(player->getBalance()), 80, true, false);
            }
            else
            {
                double balance = player->getBalance();
                player->setBalance(balance - bet);

                graphicModule->print("EU...EU...EU...Você se...", 25, false, false);
                graphicModule->println("Perdeu!", 25, true, false);
                graphicModule->print("Novo saldo: R$", 80, false, false);
                graphicModule->println(std::to_string(player->getBalance()), 80, true, false);
            }
            graphicModule->wait(1250);
            graphicModule->clear();
        }
    }
    else
    {
        this->graphicModule->println("Animal escolhido não encontrado.", 25, true, false);
    }

    // this->graphicModule->println(std::to_string(ApostaEscolhida), 25, true, false);
    /*
        string animalEscolhido;
        std::cin >> animalEscolhido;

        int numeroAnimal = escolherAnimal(animalEscolhido);
        if (numeroAnimal != -1)
        {
            std::cout << "Número do animal escolhido: " << numeroAnimal << std::endl;
        }
        else
        {
            std::cout << "Animal escolhido não encontrado." << std::endl;
        }

        */
}

void JogoDoBicho::mostrarAnimal()
{

    this->graphicModule->clear();
    this->graphicModule->print("Escolha um animal para apostar:\n", 14, false, true);

    int rows = 5;        // Número de linhas
    int cols = 5;        // Número de colunas
    int animalIndex = 0; // Índice do animal na lista

    // Adiciona margem superior
    this->graphicModule->println("", 25, true, false);

    for (int i = 0; i < rows; i++)
    {
        // Adiciona margem esquerda
        this->graphicModule->print("\t", 25, false, true);

        for (int j = 0; j < cols; j++)
        {
            // Verifica se ainda há animais na lista
            if (animalIndex < animais.size())
            {
                // Mostra o animal na posição atual
                this->graphicModule->print(std::to_string(animalIndex + 1) + " - " + animais[animalIndex].first + "\t", 25, false, true);
                animalIndex++;
            }
            else
            {
                // Se não houver mais animais, mostra um espaço em branco
                this->graphicModule->print("\t", 25, false, true);
            }
        }

        // Adiciona margem direita e separa as linhas por uma linha em branco
        this->graphicModule->println("\t", 25, true, false);
        this->graphicModule->println("", 25, true, false);
    }

    // Adiciona margem inferior
    this->graphicModule->println("", 25, true, false);
}

bool JogoDoBicho::sorteio(const string &tipoSorteio, int numeroEscolhido)
{
    int numeroSorteado = randomNumberGenerator->generate(0, 99); // Gera um número aleatório entre 0 e 99

    if (tipoSorteio == "Animal" || tipoSorteio == "animal")
    {
        this->graphicModule->println("Número sorteado: " + std::to_string(numeroSorteado % 25), 25, true, false);
        return numeroEscolhido == (numeroSorteado % 25) + 1; // Assumindo que há 25 animais
    }
    else if (tipoSorteio == "Dezena" || tipoSorteio == "dezena")
    {
        int DezenaEscolhida = numeroEscolhido * 4;
        int d0 = DezenaEscolhida - 3;
        int d1 = DezenaEscolhida - 2;
        int d2 = DezenaEscolhida - 1;
        int d3 = DezenaEscolhida;

        int dezenaEscolhida;
        this->graphicModule->clear();
        this->graphicModule->println("Escolha uma dezena para apostar: ", 14, false, true);
        this->graphicModule->println(std::to_string(d0) + " - " + std::to_string(d1) + " - " + std::to_string(d2) + " - " + std::to_string(d3), 14, false, false);

        dezenaEscolhida = inputModule->readIntInRange("", d0, d3);
        this->graphicModule->println("Dezena escolhida: " + std::to_string(dezenaEscolhida), 25, true, false);
        this->graphicModule->println("Número sorteado: " + std::to_string(numeroSorteado), 25, true, false);
        return dezenaEscolhida == numeroSorteado;
    }
    return false;
}

int JogoDoBicho::escolherAnimal(const string &animalEscolhido)
{
    for (const auto &animal : animais)
    {
        if (animal.first == animalEscolhido)
        {
            return animal.second;
        }
        else if (std::to_string(animal.second) == animalEscolhido)
        {
            return animal.second;
        }
    }
    return -1; // Retorna -1 se o animal não for encontrado
}

double JogoDoBicho::readBet(double minimumBet, double balance)
{
    graphicModule->println("Caso você ganhe o retorno será de até 80X o valor apostado!", 80, true, true);
    graphicModule->print("Insira o valor da aposta: ", 80, false, false);

    double bet = inputModule->readDoubleInRange("", minimumBet, balance);

    graphicModule->println("--------------------------------", 1000, true, false);
    graphicModule->wait(750);

    return bet;
}
