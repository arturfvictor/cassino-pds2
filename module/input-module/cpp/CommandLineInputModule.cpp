#include <iostream>

#include "../hpp/CommandLineInputModule.hpp"

using std::cin;

CommandLineInputModule::CommandLineInputModule(GraphicModule* graphicModule): InputModule(), graphicModule(graphicModule) {
}

int CommandLineInputModule::readInt(string text) {
    int tries = 0;
    while(tries < 3) {
        graphicModule->print(text, 50, true, false);

        try {
            return readInt();
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 50, false, false);
        }

        tries++;
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

int CommandLineInputModule::readIntInRange(string text, int start, int end) {
    int tries = 0;
    while(tries < 3) {
        try {
            int input = readInt();

            if (input < start || input > end) {
                tries++;
                throw std::invalid_argument("Entrada inválida, tente novamente. (Tipo esperado: int entre " + std::to_string(start) + " e " + std::to_string(end) + ")");
            }
            
            return input;
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 50, false, false);
        }
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

int CommandLineInputModule::readInt() {
    int input;
    cin >> input;

    if (cin.fail()) {
        // reseting cin state
        cin.clear();
        string ignore;
        std::getline(cin, ignore);

        throw std::invalid_argument("Entrada inválida, tente novamente. (Tipo esperado: int)");
    }

    return input;
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