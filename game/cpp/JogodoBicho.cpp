#include "JogoDoBicho.hpp"

JogoDoBicho::JogoDoBicho(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name) : Game(graphicModule, randomNumberGenerator, inputModule, name)
{
    // Inicializar a lista de animais diretamente no código
    animais = {
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
        {"Vaca", 25}};

    modosdeaposta = {{"Animal", 1},
                     {"Dezena", 2},
                     {"Centena", 3}};
};

void JogoDoBicho::play(Player *player)
{

    bool firstExec = true;
    bool inputValidation;

    showGameHeader(player->getName(), player->getBalance());

    this->graphicModule->clear();
    this->graphicModule->print("Escolha um modo de aposta:\n", 14, false, true); //"Escolha um animal para apostar:" << std::endl;
    int pos = 0;
    for (const auto &aposta : modosdeaposta)
    {
        string string_aux = aposta.first;
        this->graphicModule->println(std::to_string(pos) + " - " + string_aux, 10, false, true);
        pos++;
    }

    int ApostaEscolhida = inputModule->readIntInRange("", 0, modosdeaposta.size() - 1);
    if (ApostaEscolhida == 0)
    {
        ApostarAnimal();
    }
    else if (ApostaEscolhida == 1)
    {
        ApostarDezena();
    }
    else if (ApostaEscolhida == 2)
    {
        // ApostarCentena();
    }
    this->graphicModule->println(std::to_string(ApostaEscolhida), 25, true, false);
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

    int rows = 4;        // Número de linhas
    int cols = 6;        // Número de colunas
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

void JogoDoBicho::ApostarAnimal()
{
    mostrarAnimal();
    string animalEscolhido = inputModule->readString(""); // Solicita a escolha do animal
    int numeroAnimal = escolherAnimal(animalEscolhido);

    if (numeroAnimal != -1)
    {
        this->graphicModule->println("Número do animal escolhido: " + std::to_string(numeroAnimal), 25, true, false);

        // Introduzindo a pergunta para iniciar o sorteio
        string iniciarSorteio = inputModule->readString("Iniciar Sorteio? Sim ou Nao: ");
        if (iniciarSorteio == "Sim" || iniciarSorteio == "sim")
        {
            // Pergunta se é dezena ou animal
            string tipoSorteio = inputModule->readString("Deseja sortear por Dezena ou Animal? ");

            bool resultado = sorteio(tipoSorteio, numeroAnimal);
            if (resultado)
            {
                this->graphicModule->println("Parabéns! Você ganhou o sorteio!", 25, true, false);
            }
            else
            {
                this->graphicModule->println("Infelizmente, você não ganhou o sorteio.", 25, true, false);
            }
        }
    }
    else
    {
        this->graphicModule->println("Animal escolhido não encontrado.", 25, true, false);
    }
}

bool JogoDoBicho::sorteio(const string &tipoSorteio, int numeroEscolhido)
{
    int numeroSorteado = randomNumberGenerator->generate(0, 99); // Gera um número aleatório entre 0 e 99
    this->graphicModule->println("Número sorteado: " + std::to_string(numeroSorteado), 25, true, false);

    if (tipoSorteio == "Animal" || tipoSorteio == "animal")
    {
        return numeroEscolhido == (numeroSorteado % 25) + 1; // Assumindo que há 25 animais
    }
    else if (tipoSorteio == "Dezena" || tipoSorteio == "dezena")
    {

        int d0 = numeroAnimal - 3;
        int d1 = numeroAnimal - 2;
        int d2 = numeroAnimal - 1;
        int d3 = numeroAncd imal;

        int dezenaEscolhida;
        this->graphicModule->clear();
        this->graphicModule->println("Escolha uma dezena para apostar: ", 14, false, true);
        this->graphicModule->println(std::to_string(d0) + " - " + std::to_string(d1) + " - " + std::to_string(d2) + " - " + std::to_string(d3), 14, false, false);

        dezenaEscolhida = inputModule->readIntInRange("", d0, d3);
        this->graphicModule->println("Dezena escolhida: " + std::to_string(dezenaEscolhida), 25, true, false);
        return numeroEscolhido == numeroSorteado;
    }
    return false;
}

void JogoDoBicho::ApostarDezena()
{

    mostrarAnimal();
    string animalEscolhido = inputModule->readString(""); // Solicita a escolha do animal
    int numeroAnimal = escolherAnimal(animalEscolhido);

    if (numeroAnimal != -1)
    {
        this->graphicModule->println("Número do animal escolhido: " + std::to_string(numeroAnimal), 25, true, false);
    }
    else
    {
        this->graphicModule->println("Animal escolhido não encontrado.", 25, true, false);
    }

    int d0 = numeroAnimal - 3;
    int d1 = numeroAnimal - 2;
    int d2 = numeroAnimal - 1;
    int d3 = numeroAnimal;

    int dezenaEscolhida;
    this->graphicModule->clear();
    this->graphicModule->println("Escolha uma dezena para apostar: ", 14, false, true);
    this->graphicModule->println(std::to_string(d0) + " - " + std::to_string(d1) + " - " + std::to_string(d2) + " - " + std::to_string(d3), 14, false, false);

    dezenaEscolhida = inputModule->readIntInRange("", d0, d3);
    this->graphicModule->println("Dezena escolhida: " + std::to_string(dezenaEscolhida), 25, true, false);
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

void JogoDoBicho::showGameHeader(string name, float balance)
{
    this->graphicModule->clear();
    this->graphicModule->print("Olá, ", 25, false, false);
    this->graphicModule->println(name, 25, true, false);
    this->graphicModule->print("Saldo Atual: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(balance), 25, true, false);
    this->graphicModule->print("Aposta Mínima: ", 25, false, false);
    this->graphicModule->println("R$ " + std::to_string(0.05 * balance), 25, true, false);
}
