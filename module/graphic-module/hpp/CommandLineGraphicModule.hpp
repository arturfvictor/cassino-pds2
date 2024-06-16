#ifndef COMMANDLINEGRAPHICMODULE
#define COMMANDLINEGRAPHICMODULE

#include "./GraphicModule.hpp"

class CommandLineGraphicModule : public GraphicModule {
    private:
        int charCount;
    private:
        void enableTextFormatting(bool bold, bool underline);
        void disableTextFormatting(bool bold, bool underline);
    public:
        CommandLineGraphicModule();
        void print(string text, int speed, bool bold, bool underline) override;
        void println(string text, int speed, bool bold, bool underline) override;
        void clear() override;
};

#endif