#ifndef RANDOMNUMBERGENERATOR
#define RANDOMNUMBERGENERATOR

class RandomNumberGenerator {
    public:
        /// @brief Gera um número inteiro aleatório
        /// @return O número gerado
        virtual int generate() = 0;

        /// @brief Gera um número inteiro aleatório a partir de uma faixa
        /// @param start Inicio da faixa (Inclusivo)
        /// @param end Final da faixa (Exclusivo)
        /// @return Número gerado
        virtual int generate(int start, int end) = 0;
};

# endif