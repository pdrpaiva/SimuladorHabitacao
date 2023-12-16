//#include <iostream>
//#include <string>
//#include <iomanip>
#include "Interface/Interface.h"
#include "../lib/Terminal.h"
#include <string>
using namespace std;
using namespace term;

int main() {
    Terminal &terminal = Terminal::instance();

    GestorHabitacao* gestor = new GestorHabitacao();

    Interface* interface = new Interface(terminal,gestor);

    while (!interface->Sair())
        interface->processaComandos();

    delete gestor;
    delete interface;

    return 0;
}
