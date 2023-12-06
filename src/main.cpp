//#include <iostream>
//#include <string>
//#include <iomanip>
#include "Interface/Interface.h"
#include "../lib/Terminal.h"
#include <string>
using namespace std;
using namespace term;

int main() {
    Terminal &t = Terminal::instance();
    Interface TP(t);
    TP.processaComandos();

    return 0;
}
