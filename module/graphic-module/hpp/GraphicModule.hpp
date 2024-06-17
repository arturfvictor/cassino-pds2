#ifndef GRAPHICMODULE
#define GRAPHICMODULE

#include <string>

using std::string;

class GraphicModule {
    public:
        /// @brief Imprime texto em tela
        /// @param text Texo a ser impresso
        /// @param speed Velocidade em caracteres por segundo em que o texto deve ser impresso
        /// @param bold Se o texto deve ser impresso em negrito
        /// @param underline Se o texto deve ser impresso sublinhado
        void virtual print(string text, int speed, bool bold, bool underline) = 0;

        /// @brief Imprime texto em tela com uma quebra de linha no final
        /// @param text Texo a ser impresso
        /// @param speed Velocidade em caracteres por segundo em que o texto deve ser impresso
        /// @param bold Se o texto deve ser impresso em negrito
        /// @param underline Se o texto deve ser impresso sublinhado
        void virtual println(string text, int speed, bool bold, bool underline) = 0;


        /// @brief Limpa a tela
        void virtual clear() = 0;

        /// @brief Freezes the game for the desired time
        /// @param millis duration in millis
        void virtual wait(int millis) = 0;
};

#endif