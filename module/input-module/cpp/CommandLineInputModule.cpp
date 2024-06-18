#include <iostream>

#include "../hpp/CommandLineInputModule.hpp"

using std::cin;

CommandLineInputModule::CommandLineInputModule(GraphicModule* graphicModule): InputModule(), graphicModule(graphicModule) {
}

int CommandLineInputModule::readInt(string text) {
    cin.clear();
    int tries = 0;
    while(tries < 3) {
        graphicModule->print(text, 80, false, false); 

        try {
            return readInt();
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 80, false, false);
           
        }

        tries++;
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

int CommandLineInputModule::readIntInRange(string text, int start, int end) {
    cin.clear();
    int tries = 0;
    while(tries < 3) {
        try {
            int input = readInt();

            if (input < start || input > end) {
                throw std::invalid_argument("Entrada inválida, tente novamente. (Tipo esperado: int entre " + std::to_string(start) + " e " + std::to_string(end) + ")");
            }

            return input;
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 80, false, false);
            
        }
        tries++;
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

int CommandLineInputModule::readInt() {
    cin.clear();
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
    cin.clear();
    int tries = 0;
    while(tries < 3) {
        graphicModule->print(text, 80, false, false);

        try {
            return readDouble();
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 80, false, false);
        }

        tries++;
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

double CommandLineInputModule::readDoubleInRange(string text, double start, double end) {
    cin.clear();
    int tries = 0;
    while(tries < 3) {
        try {
            double input = readDouble();

            if (input < start || input > end) {
                tries++;
                throw std::invalid_argument("Entrada inválida, tente novamente. (Tipo esperado: double entre " + std::to_string(start) + " e " + std::to_string(end) + ")");
            }

            return input;
        } catch (const std::invalid_argument &e) {
            graphicModule->println(e.what(), 80, false, false);
        }

        tries++;
    }
    throw std::invalid_argument("Excedido o número de tentativas!");
}

double CommandLineInputModule::readDouble() {
    cin.clear();
    double input;
    cin >> input;

    if (cin.fail()) {
        // reseting cin state
        cin.clear();
        string ignore;
        std::getline(cin, ignore);

        throw std::invalid_argument("Entrada inválida, tente novamente. (Tipo esperado: double)");
    }

    return input;
}


string CommandLineInputModule::readString(string text) {
    cin.clear();
    int tries = 0;
    while(tries < 3) {
        tries++;

        graphicModule->print(text, 80, false, true);
        graphicModule->print(" ", 80, false, false);
        
        string input;
        cin >> input;

        if (cin.fail()) {
            // reseting cin state
            cin.clear();
            string ignore;
            std::getline(cin, ignore);

            graphicModule->println("Entrada inválida, tente novamente. (Tipo esperado: string)", 80, true, true);
            
            continue;
        }

        return input;
    }

    throw std::invalid_argument("Excedido o número de tentativas!");
}