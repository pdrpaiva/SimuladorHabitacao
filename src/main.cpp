#include "Interface/Interface.h"
#include <string>
using namespace std;
using namespace term;

int main() {
    Terminal &terminal = Terminal::instance();

    Terreno* terreno = new Terreno();

    Interface* interface = new Interface(terminal,terreno);

    while (!interface->Sair())
        interface->processaComandos();

    delete terreno;
    delete interface;

    return 0;
}
