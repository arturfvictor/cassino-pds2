#ifndef COMMANDLINEINPUTMODULE
#define COMMANDLINEINPUTMODULE

#include <string>

#include "../../graphic-module/hpp/GraphicModule.hpp"
#include "./InputModule.hpp"

using std::string;

class CommandLineInputModule : public InputModule {
    private:
        GraphicModule* graphicModule;
    public:
        /// @brief Construtor do CommandLineInputModule
        /// @param graphicModule Implementação de GraphicModule que será usado para mostrar texto em tela
        CommandLineInputModule(GraphicModule* graphicModule);

        int readInt(string text) override;
        double readDouble(string text) override;
        string readString(string text) override;
};

#endif