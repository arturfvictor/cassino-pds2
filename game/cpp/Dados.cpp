#include <iostream>
#include <vector>
#include <map> // dicionário do c++
#include <string>
#include <error.h> // para .erro()
#include "../hpp/Dados.hpp"
#include <cstdlib> // Para rand() e srand()
#include <ctime>   // Para time()
#include <numeric> // Para gcd() MDC, "cppStandard": "c++17"

Dados::Dados(GraphicModule *graphicModule, RandomNumberGenerator *randomNumberGenerator, InputModule *inputModule, string name, double minimumBet) : Game(graphicModule, randomNumberGenerator, inputModule, name, minimumBet) {}

void Dados::imprime_dados(int n)
{
    if (n == 1)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|     |", 1000, false, false);
        graphicModule->println("|  *  |", 1000, false, false);
        graphicModule->println("|_____|", 1000, false, false);
    }
    else if (n == 2)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|*    |", 1000, false, false);
        graphicModule->println("|     |", 1000, false, false);
        graphicModule->println("|____*|", 1000, false, false);
    }
    else if (n == 3)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|*    |", 1000, false, false);
        graphicModule->println("|  *  |", 1000, false, false);
        graphicModule->println("|____*|", 1000, false, false);
    }
    else if (n == 4)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|*   *|", 1000, false, false);
        graphicModule->println("|     |", 1000, false, false);
        graphicModule->println("|*___*|", 1000, false, false);
    }
    else if (n == 5)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|*   *|", 1000, false, false);
        graphicModule->println("|  *  |", 1000, false, false);
        graphicModule->println("|*___*|", 1000, false, false);
    }
    else if (n == 6)
    {
        graphicModule->println(" _____", 1000, false, false);
        graphicModule->println("|*   *|", 1000, false, false);
        graphicModule->println("|*   *|", 1000, false, false);
        graphicModule->println("|*___*|", 1000, false, false);
    }
}
void Dados::escolha_2numeros(Player *player)
{
    int n1, n2;
    bool input_2numeros = false;
    bool input_rodadas = false;
    bool input_aposta = false;
    int concordar = 0;
    int rodadas;
    std::vector<int> dado1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> dado2 = {1, 2, 3, 4, 5, 6};
    std::map<int, int> dicionario_probabilidade;
    dicionario_probabilidade = {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {8, 5}, {9, 4}, {10, 3}, {11, 2}, {12, 1}};
    double probabilidade_total = 36;
    double probabilidade;
    int gerado1, gerado2;
    double aposta;
    double saldo;
    double multiplicador;
    bool venceu;

    // INPUT DE DADOS E VALIDAÇÃO DOS MESMOS
    // o loop com o try impede que o usuário digite um número diferente fora do intervalo [1:12]
    while (concordar == 0)
    {
        while (input_2numeros == false)
        {
            try
            {
                graphicModule->println("Digite dois números inteiros entre 2 à 12", 80, false, false);
                n1 = inputModule->readInt("Insira o primeiro: ");

                // std::cin >> n1 >> n2;
                if (n1 > 12 || n1 < 2)
                {
                    throw std::invalid_argument("Número inválido, digite um número entre 1 e 12");
                }
                else
                {
                    graphicModule->println("Você escolheu os números : " + std::to_string(n1), 80, false, false);
                }
                n2 = inputModule->readInt("Insira o segundo: ");
                if (n2 > 12 || n2 < 2)
                {
                    throw std::invalid_argument("Número inválido, digite um número entre 1 e 12");
                }
                else
                {
                    graphicModule->println("Você escolheu os números : " + std::to_string(n1) + " " + std::to_string(n2), 80, false, false);
                    input_2numeros = true; // sai do loop
                }
            }
            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, true, false);
                ;
            }
        }
        // escolhe em quantas rodadas o número será sorteado
        while (input_rodadas == false)
        {
            try
            {
                graphicModule->println("Digite em quantas rodadas algum dos números será sorteado ", 80, false, false);
                rodadas = inputModule->readInt("Insira a quantidade de rodadas: ");
                // std::cin >> rodadas;
                if (rodadas < 1)
                {
                    throw std::invalid_argument("Número inválido, digite um número maior que 0 e inteiro");
                }

                else
                {
                    input_rodadas = true; // sai do loop
                    graphicModule->println("Você escolheu os números " + std::to_string(n1) + " e " + std::to_string(n2), 80, false, false);
                }
            }
            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, true, false);
                ;
            }
        }
        // CALCULO DE PROBABILIDADE E RETORNO ESPERADO
        // calcular a probabilidade de sair os números escolhidos e qual é o retorno esperado

        if (n1 != n2)
        {
            probabilidade = ((dicionario_probabilidade[n1] + dicionario_probabilidade[n2]) / probabilidade_total) * rodadas;
        }
        else
        {
            probabilidade = ((dicionario_probabilidade[n1]) / probabilidade_total) * rodadas;
        }
        graphicModule->println("A probabilidade de sair os números escolhidos é de " + std::to_string(probabilidade * 100) + "%", 80, false, false);

        // multiplicador da aposta
        multiplicador = 1 / probabilidade;
        graphicModule->println("O multiplicador será: " + std::to_string(multiplicador), 80, false, false);
        ;

        // quanto o usuário quer apostar

        while (input_aposta == false)
        {
            try
            {
                graphicModule->println("Digite sua aposta ", 80, false, false);
                ;
                graphicModule->println("Obs: digite números fracionários com '.' e não ','", 80, false, true);
                ;
                aposta = inputModule->readDouble("Insira sua aposta:");

                // std::cin >> aposta;

                if (aposta < 0 || player->getBalance() < aposta)
                {
                    throw std::invalid_argument("Aposta inválida, digite um número maior que 0");
                }
                else
                {
                    input_aposta = true;
                }
            }

            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, false, false);
                ;
            }
        }

        // o usuário concorda com o retorno esperado?
        try
        {

            graphicModule->println("Você concorda com o retorno esperado de? " + std::to_string(aposta * multiplicador), 80, true, false);
            ;
            graphicModule->println(" 1-) Sim ", 80, false, false);
            ;
            graphicModule->println(" 2-) Não ", 80, false, false);
            ;
            graphicModule->println("Digite o número correspondente a sua escolha ", 80, false, false);
            concordar = inputModule->readInt("Insira a sua escolha: ");
            // std::cin >> concordar;
            if (concordar != 1 && concordar != 2)
            {
                throw std::invalid_argument("Número inválido, digite 1 ou 2");
            }
            else if (concordar != 1)
            {
                concordar = 0;
                input_2numeros = false;
                input_rodadas = false;
                input_aposta = false;
                probabilidade=0;
                
            }
            else
            {
                concordar = 1;
            }
        }
        catch (const std::exception &e)
        {
            graphicModule->println(e.what(), 80, true, false);
            ;
        }
    }
    // RODADA DE DADOS

    ;
    for (int i = 0; i < rodadas; i++)
    {
        gerado1 = randomNumberGenerator->generate(1, 7);
        gerado2 = randomNumberGenerator->generate(1, 7);
        imprime_dados(gerado1);
        imprime_dados(gerado2);
        graphicModule->println("Dados: " + std::to_string(gerado1 + gerado2), 80, true, false);
    }
        // ganhou ou perdeu
        if (gerado1 + gerado2 == n1 || gerado1 + gerado2 == n2)
        {
            venceu = true;
            graphicModule->println("Você ganhou!", 80, false, false);
            ;
        }
        else
        {
            graphicModule->println("Você perdeu!", 80, false, false);
            ;
        }
        if (venceu == true)
        {
            aposta = aposta + (aposta * multiplicador);
            graphicModule->println("Seu saldo era: " + std::to_string(player->getBalance()), 80, false, true);
            ;
            saldo = player->getBalance() + aposta; // altera o saldo do player
            graphicModule->println("Agora ele é : " + std::to_string(saldo), 80, false, true);
        }
        else{
                        graphicModule->println("Seu saldo era: " + std::to_string(player->getBalance()), 80, false, true);
            ;
            saldo = player->getBalance() - aposta; // altera o saldo do player
            graphicModule->println("Agora ele é : " + std::to_string(saldo), 80, false, true);
        }
    
}

void Dados::escolha_maior_menor(Player *player)
{
    bool input_de_escolha = false;
    bool input_numero = false;
    int concordar = 0;
    bool input_aposta = false;
    int escolha;
    int n;
    double probabilidade;
    double multiplicador;
    double soma = 0;
    double probabilidade_total = 36;
    double aposta;
    int gerado1;
    int gerado2;
    double saldo;
    bool venceu;
    std::map<int, int> dicionario_probabilidade;
    dicionario_probabilidade = {{2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {8, 5}, {9, 4}, {10, 3}, {11, 2}, {12, 1}};
    // INPUT DE DADOS E VALIDAÇÃO DOS MESMOS
    // input de escolha de maior ou menor
    while (concordar == 0)
    {
        while (input_de_escolha == false)
        {
            graphicModule->println("Digite o tipo de aposta vc quer fazer: ", 80, false, false);
            graphicModule->println("1-) Maior que: ", 80, false, false);
            graphicModule->println("2-) Menor que: ", 80, false, false);
            graphicModule->println("Digite o número correspondente a sua escolha: ", 80, false, false);

            // o loop com o try impede que o usuário digite um número diferente de 1 ou 2
            try
            {
                escolha = inputModule->readInt("Insira o tipo de aposta: ");
                // std::cin >> escolha;
                if (escolha != 1 && escolha != 2)
                {
                    throw std::invalid_argument("Número inválido, digite 1 ou 2");
                }
                else
                {
                    input_de_escolha = true;
                }
            }
            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, true, false);
                ;
            }
        }

        // insere número maior ou menor e trata eles
        while (input_numero == false)
        {
            try
            {
                graphicModule->println("Digite um números inteiro entre 3 à 11 ", 80, false, false);
                n = inputModule->readInt("Insira o número: ");
                // std::cin >> n;
                if (n > 12 || n < 2)
                {
                    throw std::invalid_argument("Número inválido, digite um número entre 3 e 11");
                }
                else
                {
                    if (escolha == 1)
                    {
                        graphicModule->println("Você escolheu que irá sortear números maiores que " + std::to_string(n), 80, false, false);
                        ;
                        input_numero = true;
                    }
                    else
                    {
                        graphicModule->println("Você escolheu que irá sortear números menores que " + std::to_string(n), 80, false, false);
                        ;
                        input_numero = true;
                    }

                    input_numero = true; // sai do loop
                }
            }
            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, true, false);
                ;
            }
        }
        // CALCULO DE PROBABILIDADE E RETORNO ESPERADO
        // calcular a probabilidade de sair os números escolhidos e qual é o retorno esperado
        if (escolha == 1) /// maior
        {
            for (int i = n + 1; i < 13; i++)
            {
                soma += dicionario_probabilidade[i];
            }
        }
        else
        {
            for (int i = 2; i < n; i++)
            {
                soma += dicionario_probabilidade[i];
            }
        }
        probabilidade = soma / probabilidade_total;
        graphicModule->println("A probabilidade de sair os números escolhidos é de " + std::to_string(probabilidade * 100) + "%", 80, false, false);
        ;
        // multiplicador da aposta
        multiplicador = 1 / probabilidade;
        graphicModule->println("O multiplicador será: " + std::to_string(multiplicador), 80, false, false);
        ;

        while (input_aposta == false)
        {
            try
            {
                graphicModule->println("Digite sua aposta: ", 80, false, false);
                ;
                graphicModule->println("Obs: digite números fracionários com '.' e não ','", 80, false, true);
                ;
                aposta = inputModule->readDouble("Insira sua aposta: ");
                // std::cin >> aposta;

                if (aposta < 0 || player->getBalance() < aposta)
                {
                    throw std::invalid_argument("Aposta inválida, digite um número maior que 0 ou que seja compativel com seu balanço");
                }
                else
                {
                    input_aposta = true;
                }
            }

            catch (const std::exception &e)
            {
                graphicModule->println(e.what(), 80, true, false);
                ;
            }
        }
        // o usuário concorda com o retorno esperado?
        try
        {

            graphicModule->println("Você concorda com o retorno esperado de " + std::to_string(aposta * multiplicador), 80, false, false);
            ;
            graphicModule->println(" 1-) Sim ", 80, false, false);
            ;
            graphicModule->println(" 2-) Não ", 80, false, false);
            ;
            graphicModule->println("Digite o número correspondente a sua escolha: ", 80, false, false);
            ;
            concordar = inputModule->readInt("Insira o primeiro: ");
            // std::cin >> concordar;
            if (concordar != 1 && concordar != 2)
            {
                throw std::invalid_argument("Número inválido, digite 1 ou 2");
            }
            else if (concordar != 1)
            {
                concordar = 0;
                input_aposta = false;
                input_de_escolha = false;
                input_numero = false;
                probabilidade=0;
                soma=0;
            }
            else
            {
                concordar = 1;
            }
        }
        catch (const std::exception &e)
        {
            graphicModule->println(e.what(), 80, true, false);
            
        }
    }
    // RODADA DE DADOS

    gerado1 = randomNumberGenerator->generate(1, 7);
    gerado2 = randomNumberGenerator->generate(1, 7);
    imprime_dados(gerado1);
    imprime_dados(gerado2);
    graphicModule->println("Dados: " + std::to_string(gerado1 + gerado2), 80, true, false);
    ;
        if (gerado1 + gerado2>n && escolha==1)
        {
            venceu = true;
            graphicModule->println("Você ganhou!", 80, false, false);
            ;
        }
        else if(gerado1 + gerado2<n && escolha==0){
            venceu = true;
            graphicModule->println("Você ganhou!", 80, false, false);
            ;
        }
        else
        {
            graphicModule->println("Você perdeu!", 80, false, false);
            ;
        }
    // ganhou ou perdeu
        if (venceu == true)
        {
            aposta = aposta + (aposta * multiplicador);
            graphicModule->println("Seu saldo era: " + std::to_string(player->getBalance()), 80, false, true);
            ;
            saldo = player->getBalance() + aposta; // altera o saldo do player
            graphicModule->println("Agora ele é : " + std::to_string(saldo), 80, false, true);
        }
        else{
                        graphicModule->println("Seu saldo era: " + std::to_string(player->getBalance()), 80, false, true);
            ;
            saldo = player->getBalance() - aposta; // altera o saldo do player
            graphicModule->println("Agora ele é : " + std::to_string(saldo), 80, false, true);
        }
}

void Dados::play(Player *player) // deu bom
{
    int tipo_de_aposta;
    bool input_de_aposta = false;
    showGameHeader(player->getName(), player->getBalance());

    // escolha o tipo de aposta
    while (input_de_aposta == false)
    {
        graphicModule->println("Qual tipo de aposta você irá fazer?", 80, false, false);
        ;
        graphicModule->println(" 1-) Escolha dois números ", 80, false, false);
        ;
        graphicModule->println(" 2-) Escolha se é maior ou menor que certo número ", 80, false, false);
        ;
        graphicModule->println("Digite o número correspondente a sua escolha: ", 80, false, false);
        // o loop com o try impede que o usuário digite um número diferente de 1 ou 2
        try
        {
            tipo_de_aposta = inputModule->readInt("Insira a sua escolha: ");
            // std::cin >> tipo_de_aposta;
            if (tipo_de_aposta != 1 && tipo_de_aposta != 2)
            {
                throw std::invalid_argument("Número inválido, digite 1 ou 2");
            }
            else
            {
                input_de_aposta = true;
            }
        }
        catch (const std::exception &e)
        {
            graphicModule->println(e.what(), 80, true, false);
            ;
        }
    }
    if (tipo_de_aposta == 1)
    {
        escolha_2numeros(player);
    }
    else
    {
        escolha_maior_menor(player);
    }
}
