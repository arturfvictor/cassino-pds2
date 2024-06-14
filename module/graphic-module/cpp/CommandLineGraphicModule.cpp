#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "../hpp/CommandLineGraphicModule.hpp"

using std::cout;
using std::endl;
using std::flush;

using namespace std::chrono;
using namespace std::this_thread;

CommandLineGraphicModule::CommandLineGraphicModule() {
    clear();
}

void CommandLineGraphicModule::print(string text, int speed, bool bold, bool underline) { //speed == chars/second
    enableTextFormatting(bold, underline);

    int waitTime = 1000 / speed; 
    for (int i = 0; i < text.size(); i++) {
        cout << text[i] << flush;
        sleep_for(milliseconds(waitTime));
    }

    disableTextFormatting(bold, underline);
}

void CommandLineGraphicModule::clear() {
    #ifdef _WIN32
    std::system("cls");
    #endif

    #ifdef _WIN64
    std::system("cls");
    #endif

    #ifdef __APPLE__
    std::system("clear");
    #endif

    #ifdef __linux__
    std::system("clear");
    #endif
}

void CommandLineGraphicModule::enableTextFormatting(bool bold, bool underline) {
    if (bold) {
        cout << "\e[1m";
    }

    if (underline) {
        cout << "\033[4m";
    }
}

void CommandLineGraphicModule::disableTextFormatting(bool bold, bool underline) {
    if (bold) {
        cout << "\e[0m";
    }

    if (underline) {
        cout << "\033[24m";
    }
}