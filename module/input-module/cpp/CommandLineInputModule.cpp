#include <iostream>

#include "../hpp/CommandLineInputModule.hpp"

using std::cin;

CommandLineInputModule::CommandLineInputModule(GraphicModule* graphicModule): graphicModule(graphicModule) {
}

int CommandLineInputModule::readInt(string text) {
    int tries = 0;
    while(tries < 3) {
        tries++;

        graphicModule->print(text, 50, true, false);
        
        int input;
        cin >> input;

        if (cin.fail()) {

            // reseting cin state
            cin.clear();
            string ignore;
            std::getline(cin, ignore);

            graphicModule->println("Entrada inválida, tente novamente. (Tipo esperado: int)", 50, true, true);
            continue;
        }

        return input;
    }

    throw std::invalid_argument("Excedido o número de tentativas!");
}

double CommandLineInputModule::readDouble(string text) {
    int tries = 0;
    while(tries < 3) {
        tries++;

        graphicModule->print(text, 50, true, true);
        graphicModule->print(" ", 50, false, false);
        
        double input;
        cin >> input;

        if (cin.fail()) {

            // reseting cin state
            cin.clear();
            string ignore;
            std::getline(cin, ignore);

            graphicModule->println("Entrada inválida, tente novamente. (Tipo esperado: double)", 50, true, true);
            continue;
        }

        return input;
    }

    throw std::invalid_argument("Excedido o número de tentativas!");
}

string CommandLineInputModule::readString(string text) {
    int tries = 0;
    while(tries < 3) {
        tries++;

        graphicModule->print(text, 50, true, true);
        graphicModule->print(" ", 50, false, false);
        
        string input;
        cin >> input;

        if (cin.fail()) {

            // reseting cin state
            cin.clear();
            string ignore;
            std::getline(cin, ignore);

            graphicModule->println("Entrada inválida, tente novamente. (Tipo esperado: string)", 50, true, true);
            continue;
        }

        return input;
    }

    throw std::invalid_argument("Excedido o número de tentativas!");
}