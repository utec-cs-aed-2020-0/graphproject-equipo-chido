#include <iostream>

#include "Tester/tester.h"
#include "Parser/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    Tester::executeExamples(); // Crear grafos ejemplos (Embellecerlo) - Ir avanzando el Readme
    Tester::executeParser(); // Que se ejecute el menú  

    return EXIT_SUCCESS;
}