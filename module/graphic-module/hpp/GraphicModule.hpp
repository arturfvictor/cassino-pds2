#ifndef GRAPHICMODULE
#define GRAPHICMODULE

#include <string>

using std::string;

class GraphicModule {
    public:
        void virtual print(string text, int speed, bool bold, bool underline) = 0; // speend == chars/second
        void virtual clear() = 0;
};

#endif