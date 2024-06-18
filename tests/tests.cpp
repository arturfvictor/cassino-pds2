#define CATCH_CONFIG_MAIN
#include "./Catch2.hpp"

#include "../module/input-module/hpp/CommandLineInputModule.hpp"
#include "../module/graphic-module/hpp/CommandLineGraphicModule.hpp"

TEST_CASE("Leitura de Inteiro", "input") {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);

    //readInt
    SECTION("O valor de retorno deve ser igual ao valor de input") {
        std::stringstream simulatedInput;
        simulatedInput << "42\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        int result = inputModule->readInt("");

        std::cin.rdbuf(orig);

        REQUIRE(result == 42);
    }

    SECTION("Não deve ser possível ler uma string na função readInt") {
        std::stringstream simulatedInput;
        simulatedInput << "a\na\na\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readInt(""));

        std::cin.rdbuf(orig);
    }

    //readIntInRange
    SECTION("O valor de retorno deve ser igual ao valor de input") {
        std::stringstream simulatedInput;
        simulatedInput << "42\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        int result = inputModule->readIntInRange("", 0, 42);

        std::cin.rdbuf(orig);

        REQUIRE(result == 42);
    }

    SECTION("Não deve ser possível ler um inteiro fora do range da função readIntInRange") {
        std::stringstream simulatedInput;
        simulatedInput << "50\n-1\n52\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readIntInRange("", 0, 42));

        std::cin.rdbuf(orig);
    }

    SECTION("Não deve ser possível ler uma string na função readIntInRange") {
        std::stringstream simulatedInput;
        simulatedInput << "a\na\na\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readIntInRange("", 0, 50));

        std::cin.rdbuf(orig);
    }
}

TEST_CASE("Leitura de Double", "input") {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);

    //readDouble
    SECTION("O valor de retorno deve ser igual ao valor de input") {
        std::stringstream simulatedInput;
        simulatedInput << "42.5\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        double result = inputModule->readDouble("");

        std::cin.rdbuf(orig);

        REQUIRE(result == 42.5);
    }

    SECTION("Não deve ser possível ler uma string na função readDouble") {
        std::stringstream simulatedInput;
        simulatedInput << "a\nb\nc\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readDouble(""));

        std::cin.rdbuf(orig);
    }

    //readIntInRange
    SECTION("O valor de retorno deve ser igual ao valor de input") {
        std::stringstream simulatedInput;
        simulatedInput << "42.5\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        double result = inputModule->readDoubleInRange("", 0, 43);

        std::cin.rdbuf(orig);

        REQUIRE(result == 42.5);
    }

    SECTION("Não deve ser possível ler um inteiro fora do range da função readDoubleInRange") {
        std::stringstream simulatedInput;
        simulatedInput << "0.6\n-1.5\n105.3\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readDoubleInRange("", 10, 15));

        std::cin.rdbuf(orig);
    }

    SECTION("Não deve ser possível ler uma string na função readDoubleInRange") {
        std::stringstream simulatedInput;
        simulatedInput << "a\na\na\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        REQUIRE_THROWS(inputModule->readDoubleInRange("", 0, 50));

        std::cin.rdbuf(orig);
    }
}

TEST_CASE("Leitura de String", "input") {
    GraphicModule* graphicModule = new CommandLineGraphicModule();
    InputModule* inputModule = new CommandLineInputModule(graphicModule);

    //readString
    SECTION("O valor de retorno deve ser igual ao valor de input") {
        std::stringstream simulatedInput;
        simulatedInput << "StringDeTeste\n";

        std::streambuf* orig = std::cin.rdbuf();
        std::cin.rdbuf(simulatedInput.rdbuf());

        string result = inputModule->readString("");

        std::cin.rdbuf(orig);

        REQUIRE(result == "StringDeTeste");
    }
}

