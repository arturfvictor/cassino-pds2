#ifndef INPUTMODULE
#define INPUTMODULE

#include <string>

#include "../../graphic-module/hpp/GraphicModule.hpp"

using std::string;

class InputModule {
    private:
        GraphicModule* graphicModule;
    public:
        /// @brief Lê um inteiro do teclado
        /// @param text Texto que deve ser mostrado em tela antes da leitura
        /// @return O inteiro lido
        /// @throws `invalid_argument` - Caso aconteçam 3 tentativas falhas de leitura 
        virtual int readInt(string text) = 0;

        /// @brief Lê um inteiro do teclado e valida se ele está dentro da faixa
        /// @param text Texto que deve ser mostrado em tela antes da leitura
        /// @param start Começo da faixa
        /// @param end Fim da faixa
        /// @return O inteiro lido
        virtual int readIntInRange(string text, int start, int end) = 0;
        
        /// @brief Lê um double do teclado
        /// @param text Texto que deve ser mostrado em tela antes da leitura
        /// @return O double lido
        /// @throws `invalid_argument` - Caso aconteçam 3 tentativas falhas de leitura 
        virtual double readDouble(string text) = 0;

        /// @brief Lê um double do teclado e valida se ele está dentro da faixa
        /// @param text Texto que deve ser mostrado em tela antes da leitura
        /// @param start Começo da faixa
        /// @param end Fim da faixa
        /// @return O double lido
        virtual double readDoubleInRange(string text, double start, double end) = 0;

        /// @brief Lê uma string do teclado
        /// @param text Texto que deve ser mostrado em tela antes da leitura
        /// @return A string lida
        /// @throws `invalid_argument` Caso aconteçam 3 tentativas falhas de leitura 
        virtual string readString(string text) = 0;
};

#endif