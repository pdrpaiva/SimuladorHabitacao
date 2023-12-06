//
// Created by Utilizador on 27/10/2023.
//

#ifndef TRABALHO_HABITACAO_H
#define TRABALHO_HABITACAO_H
#include <vector>
#include <iostream>
#include "../../lib/Terminal.h"
#include "../Zonas/Zona.h"

class Habitacao {
private:
    vector<Zona *> zonas;
public:
    Habitacao();
    ~Habitacao();
};


#endif //TRABALHO_HABITACAO_H
